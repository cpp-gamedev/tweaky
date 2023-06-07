#include <whackx/app.hpp>
#include <filesystem>
#include <iostream>

namespace {
namespace fs = std::filesystem;

fs::path find_data(fs::path exe_path) {
	for (auto path = exe_path.parent_path(); !path.empty() && path != path.parent_path(); path = path.parent_path()) {
		auto ret = path / "data";
		if (fs::is_directory(ret)) { return ret; }
	}
	return {};
}
} // namespace

int main(int argc, char** argv) {
	try {
		if (argc < 1) {
			std::cerr << "Cannot determine data path\n";
			return EXIT_FAILURE;
		}

		auto data_path = find_data(argv[0]);
		if (data_path.empty()) {
			std::cerr << "Could not locate data\n";
			return EXIT_FAILURE;
		}

		whackx::App{}.run(data_path.generic_string());

	} catch (std::exception const& e) {
		std::cerr << "Fatal error: " << e.what() << "\n";
		return EXIT_FAILURE;
	}
}
