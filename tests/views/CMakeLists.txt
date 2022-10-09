add_executable( viewUtilsTests 
    viewUtilsTests.cc
)

target_link_libraries(
    viewUtilsTests 
    GTest::gtest_main
    viewUtils
)

target_include_directories(
    viewUtilsTests 
    PUBLIC
    ${CMAKE_BINARY_DIR}/src
) 


add_executable( bridgeTerminalViewTests 
    bridgeTerminalViewTests.cc
)

target_link_libraries(
    bridgeTerminalViewTests 
    GTest::gtest_main
    bridgeTerminalView
)

target_include_directories(
    bridgeTerminalViewTests 
    PUBLIC
    ${CMAKE_BINARY_DIR}/src
) 

include(GoogleTest)
gtest_discover_tests(viewUtilsTests)
gtest_discover_tests(bridgeTerminalViewTests)
