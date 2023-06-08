#include <whackx/io.hpp>
#include <filesystem>

namespace whackx {
namespace {
namespace fs = std::filesystem;

fs::path find_or_create_dir(fs::path exe_path, std::string_view data_dir_uri) {
	for (auto path = exe_path.parent_path(); !path.empty() && path != path.parent_path(); path = path.parent_path()) {
		auto ret = path / data_dir_uri;
		if (fs::is_directory(ret)) { return ret; }
	}
	// not found, try the working directory
	auto ret = fs::current_path() / data_dir_uri;
	// attempt to create subdirectory if it doesn't exit
	if (!fs::exists(ret) && !fs::create_directories(ret)) {
		// failed
		return {};
	}

	return ret;
}

std::string g_exe_path{};
std::string g_data_dir{};
} // namespace

bool io::find_or_create_data(std::string exe_path, std::string_view data_dir_uri) {
	g_exe_path = std::move(exe_path);
	auto data_dir = find_or_create_dir(g_exe_path, data_dir_uri);
	if (data_dir.empty()) { return {}; }
	g_data_dir = data_dir.generic_string();
	return true;
}

std::string_view io::exe_path() { return g_exe_path; }
std::string_view io::data_dir() { return g_data_dir; }

std::string io::data_path(std::string_view uri) { return (fs::path{g_data_dir} / uri).generic_string(); }
} // namespace whackx
