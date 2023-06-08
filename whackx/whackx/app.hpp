#pragma once
#include <gvdi/gvdi.hpp>
#include <whackx/game.hpp>

namespace whackx {
struct App {
	void run();

	gvdi::Instance gvdi{{400.0f, 400.0f}, "Whackx"};
	Game game{};
};
} // namespace whackx
