cmake_minimum_required(VERSION 3.10)

# set the project name
project(J3Engine VERSION 0.0.1)

configure_file(src/Info.h.in Info.h)

file(GLOB_RECURSE J3Engine_SRC "src/*.h" "src/*.cpp")
file(GLOB_RECURSE J3Engine_LIB "lib/*.hpp" "lib/*.cpp")

# add the executable
add_executable(J3Engine ${J3Engine_SRC})

target_include_directories(J3Engine PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(J3Engine PUBLIC "lib/")
