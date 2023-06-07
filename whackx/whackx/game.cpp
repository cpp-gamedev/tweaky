#include <imgui.h>
#include <whackx/defines.hpp>
#include <whackx/game.hpp>
#include <random>

namespace whackx {
namespace {
template <std::integral Type>
Type random_range(Type lo, Type hi) {
	static auto engine = std::default_random_engine{std::random_device{}()};
	return std::uniform_int_distribution<Type>{lo, hi}(engine);
}

void init_tweaky_db() {
	using Int = tweaky::IntData;
	using Float = tweaky::FloatData;
	auto map = tweaky::db::Map{
		{"rows", Int{.value = 3, .range = {.min = 2, .max = 10}}},
		{"columns", Int{.value = 3, .range = {.min = 2, .max = 10}}},
		{"swap_rate (s)", Float{.value = 0.5f, .range = {.min = 0.1f, .max = 2.0f}}},
	};
	tweaky::db::overwrite(std::move(map));
}

struct Inspector : tweaky::Inspector {
	bool inspect(std::string_view id, tweaky::IntData& out) final { return ImGui::SliderInt(id.data(), &out.value, out.range.min, out.range.max); }
	bool inspect(std::string_view id, tweaky::FloatData& out) final { return ImGui::SliderFloat(id.data(), &out.value, out.range.min, out.range.max); }
};
} // namespace

Position Position::make_random(std::uint32_t max_rows, std::uint32_t max_columns) {
	return Position{
		.row = random_range(0u, max_rows - 1),
		.column = random_range(0u, max_columns - 1),
	};
}

Game::Game() {
	init_tweaky_db();
	randomize_target();
}

void Game::tick(std::chrono::duration<float> dt) {
	elapsed += dt;
	if (elapsed.count() >= swap_rate || is_target_out_of_bounds()) { randomize_target(); }

	if (ImGui::Begin("Whackx", {}, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Click the X!");
		ImGui::TextColored({1.0f, 1.0f, 0.0f, 1.0f}, "Score: %d", score);
		for (std::uint32_t row = 0; row < rows; ++row) {
			for (std::uint32_t column = 0; column < columns; ++column) {
				bool const is_target = Position{row, column} == target;
				std::string button_id = is_target ? " X " : "   ";
				button_id += "##" + std::to_string(row) + std::to_string(column);
				if (ImGui::Button(button_id.c_str()) && is_target) { increment_score(); }
				if (column + 1 < columns) { ImGui::SameLine(); }
			}
		}
	}
	ImGui::End();

	if constexpr (inspector_v) { inspect(); }
}

bool Game::is_target_out_of_bounds() const { return target.row >= rows || target.column >= columns; }

void Game::increment_score() {
	++score;
	randomize_target();
}

void Game::randomize_target() {
	auto const make_target = [this] { return Position::make_random(rows, columns); };
	auto new_target = make_target();
	while (new_target == target) { new_target = make_target(); }
	target = new_target;
	elapsed = {};
}

void Game::inspect() {
	if (ImGui::Begin("Inspector", {}, ImGuiWindowFlags_AlwaysAutoResize)) {
		auto inspector = Inspector{};
		tweaky::db::inspect(inspector);
		ImGui::Separator();
		if (ImGui::Button("Reset Score")) { score = {}; }
	}
	ImGui::End();
}
} // namespace whackx
