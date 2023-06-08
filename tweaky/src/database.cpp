#include <tweaky/data_io.hpp>
#include <tweaky/database.hpp>
#include <filesystem>
#include <fstream>

namespace tweaky {
namespace {
namespace fs = std::filesystem;

db::Map g_map{};
std::string g_json_path{};

template <NumericT T>
T get_number(std::string_view const id, T const fallback) {
	auto it = g_map.find(id);
	if (it == g_map.end()) { return fallback; }
	auto const& payload = it->second;
	if (!std::holds_alternative<Data<T>>(payload)) { return fallback; }
	return std::get<Data<T>>(payload).value;
}

bool to_data(dj::Json const& json, std::variant<IntData, FloatData>& out) {
	auto const type = json["type"].as_string();
	if (type == type_name<int>()) {
		auto data = IntData{};
		from_json(json, data);
		out = data;
		return true;
	} else if (type == type_name<float>()) {
		auto data = FloatData{};
		from_json(json, data);
		out = data;
		return true;
	}
	return false;
}
} // namespace

void db::overwrite(Map map) { g_map = std::move(map); }

auto db::load_or_create(std::string json_path) -> Result {
	if (!fs::is_regular_file(json_path)) {
		// attempt to create empty JSON
		auto file = std::ofstream{json_path};
		if (!file) { return Result::eError; }
		g_json_path = std::move(json_path);
		if (!g_map.empty()) {
			// store current state
			file.close();
			save();
		}
		return Result{0};
	}

	g_json_path = std::move(json_path);
	auto const json = dj::Json::from_file(g_json_path.c_str());
	auto count = int{};
	for (auto const& [id, in_data] : json.object_view()) {
		auto out_data = std::variant<IntData, FloatData>{};
		if (!to_data(in_data["data"], out_data)) { continue; }
		auto name = Name{std::string{id}};
		if (auto const label = in_data["label"].as_string(); !label.empty()) { name.set_label(std::string{label}); }
		g_map.insert_or_assign(std::move(name), out_data);
		++count;
	}
	return Result{count};
}

auto db::save() -> Result {
	if (g_json_path.empty()) { return Result::eError; }
	if (g_map.empty()) { return Result{0}; }

	auto json = dj::Json{};
	for (auto const& [name, data] : g_map) {
		auto& out_entry = json[name.identifier()];
		if (!name.label().empty()) { out_entry["label"] = name.label(); }
		auto& out_data = out_entry["data"];
		std::visit([&out_data](auto const& data) { to_json(out_data, data); }, data);
	}
	if (!json.to_file(g_json_path.c_str())) { return Result::eError; }
	return Result{static_cast<int>(g_map.size())};
}

int db::get_int(std::string_view const id, int fallback) { return get_number(id, fallback); }
float db::get_float(std::string_view const id, float fallback) { return get_number(id, fallback); }

void db::inspect(Inspector& out) {
	bool dirty{};
	for (auto& kvp : g_map) {
		auto const& name = kvp.first;
		dirty |= std::visit([&out, &name](auto& data) { return out.inspect(name, data); }, kvp.second);
	}
	if (dirty) { save(); }
}
} // namespace tweaky
