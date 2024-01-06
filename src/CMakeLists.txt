include_directories(utils)
include_directories(printers)
add_executable(life life.m.cpp utils/args_parser.cpp)
target_link_libraries(life PRIVATE fmt::fmt spdlog::spdlog)

add_test_files()