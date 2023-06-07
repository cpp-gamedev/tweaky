#include <tweaky/database.hpp>
#include <whackx/app.hpp>
#include <whackx/defines.hpp>
#include <iomanip>
#include <iostream>

namespace whackx {
namespace {
template <tweaky::NumericT Type>
void print(std::string_view id, tweaky::Data<Type>& out) {
	std::cout << id << ": " << out.value << " [" << out.range.min << " - " << out.range.max << "]\n";
}

void print_tweaky_db() {
	struct Printer : tweaky::Inspector {
		bool inspect(std::string_view id, tweaky::IntData& out) final {
			print(id, out);
			return false;
		}

		bool inspect(std::string_view id, tweaky::FloatData& out) final {
			print(id, out);
			return false;
		}
	};
	auto printer = Printer{};
	std::cout << "Tweakables:\n" << std::fixed << std::setprecision(3);
	tweaky::db::inspect(printer);
	std::cout << "\n";
}
} // namespace

void App::run(std::string_view data_path) {
	auto json_path = std::string{data_path} + "/tweakables.json";
	auto const result = tweaky::db::load(std::move(json_path));
	if (result == tweaky::db::Result::eError) { throw std::runtime_error{"Failed to init tweaky DB"}; }

	if constexpr (debug_v) { print_tweaky_db(); }

	std::cout << "Loaded " << static_cast<int>(result) << " tweakables\n";

	while (gvdi.is_running()) {
		auto frame = gvdi::Frame{gvdi};
		game.tick(frame.dt);
	}

	tweaky::db::save();
}
} // namespace whackx
