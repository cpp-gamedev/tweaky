#pragma once
#include <djson/json.hpp>
#include <tweaky/data.hpp>

namespace tweaky {
template <typename Type>
constexpr std::string_view type_name() {
	if constexpr (std::integral<Type>) {
		return "int";
	} else {
		return "float";
	}
}

template <NumericT Type>
void from_json(dj::Json const& json, Data<Type>& out) {
	auto const type = json["type"].as_string();
	if (type != type_name<Type>()) { return; }
	out.value = json["value"].as<Type>();
	auto const& range = json["range"];
	out.range.min = range["min"].as<Type>();
	out.range.max = range["max"].as<Type>();
}

template <NumericT Type>
void to_json(dj::Json& out, Data<Type> const& data) {
	out["type"] = type_name<Type>();
	out["value"] = data.value;
	auto& range = out["range"];
	range["min"] = data.range.min;
	range["max"] = data.range.max;
}
} // namespace tweaky
