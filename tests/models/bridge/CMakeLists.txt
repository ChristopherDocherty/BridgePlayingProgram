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



configure_file(testBoards.json .)

add_executable(
    bridgeGamestateTests
    bridgeGamestateTests.cc
)
    
target_link_libraries(
    bridgeGamestateTests
    GTest::gtest_main
    bridgeGamestate
    Boost::json
)

target_include_directories(
    bridgeGamestateTests 
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
) 


include(GoogleTest)
gtest_discover_tests(bridgeCardTests)
gtest_discover_tests(bridgeGamestateTests)
