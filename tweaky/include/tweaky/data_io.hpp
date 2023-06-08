#pragma once
#include <djson/json.hpp>
#include <tweaky/data.hpp>

namespace tweaky {
template <typename Type>
constexpr std::string_view type_name() {
	if constexpr (std::integral<Type>) {
		return "int";
	} else if constexpr (std::floating_point<Type>) {
		return "float";
	} else if constexpr (std::same_as<Type, Boolean>) {
		return "Boolean";
	} else {
		return "unknown";
	}
}

template <NumericT Type>
void from_json(dj::Json const& json, NumericData<Type>& out) {
	auto const type = json["type"].as_string();
	if (type != type_name<Type>()) { return; }
	out.value = json["value"].as<Type>();
	auto const& range = json["range"];
	out.range.min = range["min"].as<Type>();
	out.range.max = range["max"].as<Type>();
}

template <NumericT Type>
void to_json(dj::Json& out, NumericData<Type> const& data) {
	out["type"] = type_name<Type>();
	out["value"] = data.value;
	auto& range = out["range"];
	range["min"] = data.range.min;
	range["max"] = data.range.max;
}

inline void from_json(dj::Json const& json, BoolData& out) {
	auto const type = json["type"].as_string();
	if (type != type_name<Boolean>()) { return; }
	out.value = json["value"].as<bool>();
}

inline void to_json(dj::Json& out, BoolData const& data) {
	out["type"] = type_name<Boolean>();
	out["value"] = dj::Boolean{data.value};
}
} // namespace tweaky
