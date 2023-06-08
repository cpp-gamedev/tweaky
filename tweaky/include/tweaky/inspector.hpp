#pragma once
#include <tweaky/data.hpp>
#include <tweaky/name.hpp>

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
	virtual bool inspect(Name const& name, IntData& out) = 0;
	///
	/// \brief Inspect a tweaky float data object.
	/// \returns true if modified.
	///
	virtual bool inspect(Name const& name, FloatData& out) = 0;
	///
	/// \brief Inspect a tweaky boolean data object.
	/// \returns true if modified.
	///
	virtual bool inspect(Name const& name, BoolData& out) = 0;
};
} // namespace tweaky
