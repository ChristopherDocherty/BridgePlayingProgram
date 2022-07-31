add_executable(
    converterTests 
    converterTests.cc
)

target_link_libraries(
    converterTests 
    GTest::gtest_main
    utils 
)

target_include_directories(
    converterTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 


include(GoogleTest)
gtest_discover_tests(converterTests)
