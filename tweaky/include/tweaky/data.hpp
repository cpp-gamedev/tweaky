#pragma once
#include <concepts>

namespace tweaky {
///
/// \brief Concept for an integral or floating point type.
///
template <typename Type>
concept NumericT = std::integral<Type> || std::floating_point<Type>;

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
struct Data {
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
using IntData = Data<int>;
///
/// \brief Alias for float Data.
///
using FloatData = Data<float>;
} // namespace tweaky
