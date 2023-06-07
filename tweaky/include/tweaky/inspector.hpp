#pragma once
#include <tweaky/data.hpp>
#include <string_view>

namespace tweaky {
///
/// \brief Customization point for tweaky data entries.
///
struct Inspector {
	virtual ~Inspector() = default;

	///
	/// \brief Inspect a tweaky int data object.
	/// \returns true if modified.
	///
	virtual bool inspect(std::string_view id, IntData& out) = 0;
	///
	/// \brief Inspect a tweaky float data object.
	/// \returns true if modified.
	///
	virtual bool inspect(std::string_view id, FloatData& out) = 0;
};
} // namespace tweaky
