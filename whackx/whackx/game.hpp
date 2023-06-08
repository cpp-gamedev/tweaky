#pragma once
#include <tweaky/value.hpp>
#include <chrono>

namespace whackx {
struct Position {
	std::uint32_t row{};
	std::uint32_t column{};

	static Position make_random(std::uint32_t max_rows, std::uint32_t max_columns);

	bool operator==(Position const&) const = default;
};

struct Game {
	Game();

	void tick(std::chrono::duration<float> dt);

	bool is_target_out_of_bounds() const;
	void increment_score();
	void randomize_target();

	void inspect();

	tweaky::Value<std::uint32_t> rows{"rows"};
	tweaky::Value<std::uint32_t> columns{"columns"};
	tweaky::Value<float> swap_rate{"swap_rate"};

	std::chrono::duration<float> elapsed{};
	Position target{};
	int score{};
};
} // namespace whackx
