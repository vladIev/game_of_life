add_executable(life life.m.cpp utils/args_parser.cpp)
target_link_libraries(life PRIVATE fmt::fmt spdlog::spdlog)
target_include_directories(life PRIVATE src)

add_test_files()