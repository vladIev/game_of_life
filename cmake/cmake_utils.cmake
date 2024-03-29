function(add_test_files)
    # Parse function arguments
    set(LIBRARIES ${ARGN} ${GTEST_BOTH_LIBRARIES} fmt::fmt spdlog::spdlog)
    # Find all test files in the directory
    file(GLOB_RECURSE TEST_FILES "*.g.cpp")
    file(GLOB_RECURSE CPP_FILES "*.cpp")
    # Exclude files with postfix ".m.cpp" or ".g.cpp"
    list(FILTER CPP_FILES EXCLUDE REGEX "\\.m\\.cpp$|\\.g\\.cpp$")
    # Create a test target for each test file
    foreach(TEST_FILE ${TEST_FILES})
        # Extract the test name from the file name
        message("Found gtest file: ${TEST_FILE}")
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        set(TEST_TARGET "${TEST_NAME}.g")

        # Create a test target for this file
        message("add_executable(${TEST_TARGET} ${TEST_FILE}  ${CPP_FILES})")
        add_executable(${TEST_TARGET} ${TEST_FILE}  ${CPP_FILES})
        target_link_libraries(${TEST_TARGET} ${LIBRARIES})

        # Register this test with CTest
        add_test(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
    endforeach()
endfunction(add_test_files)
