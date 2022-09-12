include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.1.0
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)
add_executable(range_test range_test.cpp)
target_link_libraries(range_test PRIVATE range::range Catch2::Catch2WithMain)
target_compile_options(range_test PRIVATE -std=c++17)
catch_discover_tests(range_test)
