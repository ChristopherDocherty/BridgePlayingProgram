add_subdirectory(utils)

add_executable(
    bridgeCardTests 
    bridgeCardTests.cc
)

target_link_libraries(
    bridgeCardTests 
    GTest::gtest_main
    bridgeCard
)

target_include_directories(
    bridgeCardTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 


include(GoogleTest)
gtest_discover_tests(bridgeCardTests)
