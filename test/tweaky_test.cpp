#include <tweaky/value.hpp>
#include <cstdint>
#include <iostream>
#include <numbers>

namespace {
void fail(std::string_view expression, std::int64_t line) {
	std::cerr << "Failure: expression \"" << expression << "\" evaluated to false on line " << line << "\n";
}

int g_failed{};

bool do_expect(bool predicate, std::string_view expression, std::int64_t line) {
	if (predicate) { return true; }
	++g_failed;
	fail(expression, line);
	return false;
}

#define EXPECT(predicate) do_expect(!!(predicate), #predicate, __LINE__)

bool nearly_equal(float const a, float const b, float const epsilon = 0.001f) { return std::abs(a - b) < epsilon; }

void perform_tests() {
	using namespace tweaky;

	auto map = db::Map{
		{"forty_two", IntData{.value = 42}},
		{"pi", FloatData{.value = std::numbers::pi_v<float>}},
		{"universe", BoolData{.value = true}},
	};
	db::overwrite(std::move(map));

	EXPECT(tweaky::Value<int>{"forty_two"} == 42);
	EXPECT(nearly_equal(tweaky::Value<float>{"pi"}, std::numbers::pi_v<float>));
	EXPECT(tweaky::Value<bool>{"universe"});
}
} // namespace

int main() {
	try {
		perform_tests();
	} catch (std::exception const& e) {
		std::cerr << "Fatal error: " << e.what();
		return EXIT_FAILURE;
	}

	if (g_failed) {
		std::cerr << "\n" << g_failed << " test cases failed\n";
		return EXIT_FAILURE;
	}
}
