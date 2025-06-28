# tests/CMakeLists.txt
# Gather test files
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Game/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
)

# include actual production .cpp files
file(GLOB_RECURSE PROD_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_SOURCE_DIR}/src/**/*.cpp
)

add_executable(BowlingGameTests
    ${TEST_SOURCES}
    ${PROD_SOURCES}
)

target_include_directories(BowlingGameTests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(BowlingGameTests
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(BowlingGameTests)
