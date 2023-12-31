add_executable(life life.m.cpp)
target_link_libraries(life PRIVATE fmt::fmt spdlog::spdlog)

add_test_files()