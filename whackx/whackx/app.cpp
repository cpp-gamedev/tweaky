#include <tweaky/database.hpp>
#include <whackx/app.hpp>
#include <whackx/defines.hpp>
#include <whackx/io.hpp>
#include <iomanip>
#include <iostream>

namespace whackx {
namespace {
constexpr std::string_view json_uri_v{"tweakables.json"};

template <tweaky::NumericT Type>
void print(tweaky::Name const& name, tweaky::NumericData<Type>& out) {
	std::cout << name.identifier() << ": " << out.value << " [" << out.range.min << " - " << out.range.max << "]\n";
}

void print_tweaky_db() {
	struct Printer : tweaky::Inspector {
		bool inspect(tweaky::Name const& name, tweaky::IntData& out) final {
			print(name, out);
			return false;
		}

		bool inspect(tweaky::Name const& name, tweaky::FloatData& out) final {
			print(name, out);
			return false;
		}

		bool inspect(tweaky::Name const& name, tweaky::BoolData& out) final {
			std::cout << name.identifier() << ": " << std::boolalpha << out.value << "\n";
			return false;
		}
	};
	auto printer = Printer{};
	std::cout << "Tweakables:\n" << std::fixed << std::setprecision(3);
	tweaky::db::inspect(printer);
	std::cout << "\n";
}
} // namespace

void App::run() {
	// load or create JSON
	auto const result = tweaky::db::load_or_create(io::data_path(json_uri_v));
	// early exit on error, as persistence won't work
	if (result == tweaky::db::Result::eError) { throw std::runtime_error{"Failed to init tweaky DB"}; }

	// print out each tweakable in the database
	if constexpr (debug_v) { print_tweaky_db(); }

	std::cout << "Loaded " << static_cast<int>(result) << " tweakables from " << json_uri_v << "\n";

	// run game loop
	while (gvdi.is_running()) {
		auto frame = gvdi::Frame{gvdi};
		game.tick(frame.dt);
	}

	// save database to disk before exiting
	tweaky::db::save();
}
} // namespace whackx
