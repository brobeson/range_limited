#include "range/range.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <string>
#include <type_traits>

SCENARIO("A range should be trivial") {
  CHECK(std::is_trivial_v<range::range<int>>);
  CHECK(!std::is_trivial_v<range::range<std::string>>);
}

SCENARIO("A user can query if a value is in range") {
  GIVEN("A range") {
    constexpr range::range<int> bounds{1, 5};
    AND_GIVEN("A value") {
      const auto [v, expected]{GENERATE(table<int, bool>({{0, false},
                                                          {1, true},
                                                          {2, true},
                                                          {3, true},
                                                          {4, true},
                                                          {5, true},
                                                          {6, false}}))};
      // constexpr int value{3};
      WHEN("The value is checked for being in the range") {
        THEN("The result is correct") {
          CHECK(range::in(v, bounds) == expected);
        }
      }
    }
  }
}

SCENARIO("A user can query if a value is out of range") {
  GIVEN("A range") {
    constexpr range::range<int> bounds{1, 5};
    AND_GIVEN("A value") {
      const auto [v, expected]{GENERATE(table<int, bool>({{0, true},
                                                          {1, false},
                                                          {2, false},
                                                          {3, false},
                                                          {4, false},
                                                          {5, false},
                                                          {6, true}}))};
      // constexpr int value{3};
      WHEN("The value is checked for being outside the range") {
        THEN("The result is correct") {
          CHECK(range::out(v, bounds) == expected);
        }
      }
    }
  }
}
