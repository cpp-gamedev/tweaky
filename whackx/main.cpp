#include <whackx/app.hpp>
#include <whackx/defines.hpp>
#include <whackx/io.hpp>
#include <iostream>

namespace {
constexpr std::string_view data_dir_v{"whackx-data"};
} // namespace

int main(int argc, char** argv) {
	try {
		if (argc < 1) {
			std::cerr << "Cannot determine data directory\n";
			return EXIT_FAILURE;
		}

		if (!whackx::io::find_or_create_data(argv[0], data_dir_v)) {
			std::cerr << "Could not locate / create data directory\n";
			return EXIT_FAILURE;
		}

		if constexpr (whackx::debug_v) { std::cout << "Using data directory: " << whackx::io::data_dir() << "\n"; }

		whackx::App{}.run();

	} catch (std::exception const& e) {
		std::cerr << "Fatal error: " << e.what() << "\n";
		return EXIT_FAILURE;
	}
}
