#pragma once
#include <gvdi/gvdi.hpp>
#include <whackx/game.hpp>

namespace whackx {
struct App {
	void run(std::string_view data_path);

	gvdi::Instance gvdi{{400.0f, 400.0f}, "Whackx"};
	Game game{};
};
} // namespace whackx
