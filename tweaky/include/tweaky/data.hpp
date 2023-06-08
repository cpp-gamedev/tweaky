#pragma once
#include <concepts>

namespace tweaky {
///
/// \brief Strongly typed boolean wrapper.
///
struct Boolean {
	bool value{};

	explicit constexpr operator bool() const { return value; }

	bool operator==(Boolean const&) const = default;
};

///
/// \brief Concept for an integral or floating point type.
///
template <typename Type>
concept NumericT = std::integral<Type> || std::floating_point<Type>;

///
/// \brief Concept for all valid tweaky data types.
///
template <typename Type>
concept DataTypeT = NumericT<Type> || std::same_as<Type, Boolean>;

///
/// \brief Numeric range (inclusive).
///
template <NumericT Type>
struct InclusiveRange {
	///
	/// \brief Minimum value.
	///
	Type min{};
	///
	/// \brief Maximum value.
	///
	Type max{};
};

///
/// \brief Numeric data describing a tweakable.
///
template <NumericT Type>
struct NumericData {
	///
	/// \brief Current value.
	///
	Type value{};
	///
	/// \brief Range of value.
	///
	InclusiveRange<Type> range{};
};

///
/// \brief Alias for int Data.
///
using IntData = NumericData<int>;
///
/// \brief Alias for float Data.
///
using FloatData = NumericData<float>;
///
/// \brief Alias for Boolean data.
///
using BoolData = Boolean;
} // namespace tweaky
