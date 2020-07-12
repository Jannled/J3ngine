cmake_minimum_required(VERSION 3.10)

# set the project name
project(J3Engine VERSION 0.0.1)

configure_file(src/Info.h.in Info.h)

# add the executable
add_executable(J3Engine src/TestMain.cpp)

target_include_directories(J3Engine PUBLIC "${PROJECT_BINARY_DIR}")