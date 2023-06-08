#pragma once
#include <string>

namespace tweaky {
///
/// \brief Identifier for a tweaky Value.
///
/// Supports an alternative label, which is the identifier by default.
///
class Name {
  public:
	struct Hasher;

	///
	/// \brief Contsruct from a literal identifier.
	///
	Name(char const* identifier) : Name(std::string{identifier}) {}
	///
	/// \brief Construct from an identifier.
	///
	explicit Name(std::string identifier) : m_id(std::move(identifier)), m_hash(std::hash<std::string>{}(m_id)) {}
	///
	/// \brief Construct from an identifier and a label.
	///
	Name(std::string identifier, std::string label) : m_id(std::move(identifier)), m_label(std::move(label)), m_hash(std::hash<std::string>{}(m_id)) {}

	///
	/// \brief Obtain the identifier.
	///
	std::string_view identifier() const { return m_id; }
	///
	/// \brief Obtain the label.
	///
	std::string_view label() const { return m_label.empty() ? m_id : m_label; }
	///
	/// \brief Check if label is distinct from ID.
	///
	bool has_distinct_label() const { return !m_label.empty(); }

	///
	/// \brief Override the label.
	///
	void set_label(std::string label) { m_label = std::move(label); }

	bool operator==(Name const& rhs) const { return identifier() == rhs.identifier(); }
	bool operator==(std::string_view const id) const { return identifier() == id; }
	std::size_t hash() const { return m_hash; }

  private:
	std::string m_id{};
	std::string m_label{};
	std::size_t m_hash{};
};

///
/// \brief Transparent hasher for heterogeneous lookup of Names and string_views.
///
struct Name::Hasher {
	using is_transparent = void;

	std::size_t operator()(std::string_view const type) const { return std::hash<std::string_view>{}(type); }
	std::size_t operator()(Name const& name) const { return name.hash(); }
};
} // namespace tweaky
