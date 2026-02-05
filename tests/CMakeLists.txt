# Deps
FetchContent_Declare(
    unit_test
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(unit_test)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Build
add_executable(
    tests
    main.cpp
)

target_link_libraries(tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests)
