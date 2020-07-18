cmake_minimum_required(VERSION 3.10)

# set the project name
project(J3Engine VERSION 0.0.1)

# Get the current git hash
execute_process(
    COMMAND
        git rev-parse --short HEAD
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE
        SHORT_HASH_RESULT
    OUTPUT_VARIABLE
        SHORT_HASH
)

message("Git Hash is: ${SHORT_HASH}")
configure_file(src/Window/Platform.h.in Window/Platform.h)

file(GLOB_RECURSE J3Engine_SRC "src/*.h" "src/*.hpp" "src/*.cpp")
file(GLOB_RECURSE J3Engine_LIB "lib/*.hpp" "lib/*.h" "lib/*.cpp" "lib/*.c")

# add the executable
add_executable(J3Engine ${J3Engine_SRC} ${J3Engine_LIB})

target_include_directories(J3Engine PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(J3Engine PUBLIC "src/")
target_include_directories(J3Engine PUBLIC "lib/")
