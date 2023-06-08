#pragma once
#include <tweaky/database.hpp>

namespace tweaky {
///
/// \brief "Pointer" to a tweaky value in the database, identified by its string ID.
///
template <DataTypeT Type>
class Value {
  public:
	///
	/// \brief Construct a Value by binding its ID.
	///
	explicit Value(std::string id) : m_id(std::move(id)) {}

	///
	/// \brief Obtain the tweaky value associated with this object's ID.
	///
	Type get() const { return db::get<Type>(m_id); }

	///
	/// \brief Conversion operator.
	///
	explicit(std::same_as<Type, bool>) operator Type() const { return get(); }

  private:
	std::string m_id{};
};
} // namespace tweaky
