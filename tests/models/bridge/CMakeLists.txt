configure_file(testBoards.json .)
configure_file(data/test_1.json .)

add_executable(
    bridgeTests 
    utils/converterTests.cc
    bridgeCardTests.cc
    bridgeGamestateTests.cc
    bridgeGamestateLoaderTests.cc
    bridgeGamestateLoaderTests_new.cc
)

target_link_libraries(
    bridgeTests 
    Catch2::Catch2WithMain
    bridgeGamestate
    tl::expected
)

target_include_directories(
    bridgeTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 
include(CTest)
include(Catch)
catch_discover_tests(bridgeTests)
