#pragma once
#include <tweaky/inspector.hpp>
#include <tweaky/name.hpp>
#include <string>
#include <unordered_map>
#include <variant>

namespace tweaky::db {
///
/// \brief Map of IDs to tweaky Data types.
///
using Map = std::unordered_map<Name, std::variant<IntData, FloatData>, Name::Hasher, std::equal_to<>>;

///
/// \brief Strongly typed integral result.
///
enum struct Result : int {
	eError = -1,
};

///
/// \brief Overwrite database with map.
/// \param map data to overwrite.
///
void overwrite(Map map);
///
/// \brief Load database from json_path, or create empty file if it doesn't exist.
/// \returns Result::eError on failure, else number of entries loaded.
/// \param json_path path to JSON file.
///
Result load_or_create(std::string json_path);
///
/// \brief Save loaded database.
/// \returns Result::eError on failure or if no database has been loaded, else number of entries saved.
///
Result save();

///
/// \brief Obtain a tweaky int value.
/// \returns value if data is in map, else fallback.
///
int get_int(std::string_view id, int fallback = {});
///
/// \brief Obtain a tweaky float value.
/// \returns value if data is in map, else fallback.
///
float get_float(std::string_view id, float fallback = {});

///
/// \brief Obtain a tweaky numeric value.
/// \returns value if data is in map, else fallback.
///
template <NumericT Type>
Type get(std::string_view const id) {
	if constexpr (std::integral<Type>) {
		return static_cast<Type>(get_int(id));
	} else {
		return static_cast<Type>(get_float(id));
	}
}

///
/// \brief Inspect each tweaky data entry in the database.
///
void inspect(Inspector& out);
} // namespace tweaky::db
