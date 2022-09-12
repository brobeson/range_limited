cmake_minimum_required(VERSION 3.23)

project(
  range
  VERSION 0.0.0
  LANGUAGES CXX
  DESCRIPTION "Operations related to lower and upper bounds"
  HOMEPAGE_URL "https://github.com/brobeson/range"
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE "${PROJECT_SOURCE_DIR}/include")

include(CTest)
if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
