add_subdirectory(utils)

configure_file(testBoards.json .)

add_executable(
    bridgeTests 
    bridgeCardTests.cc
    bridgeGamestateLoaderTests.cc
)

target_link_libraries(
    bridgeTests 
    Catch2::Catch2WithMain
    bridgeCard
    bridgeGamestate
)

target_include_directories(
    bridgeTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 
include(CTest)
include(Catch)
catch_discover_tests(bridgeTests)


#
#add_executable(
#    bridgeGamestateTests
#    bridgeGamestateTests.cc
#)
#    
#target_link_libraries(
#    bridgeGamestateTests
#    Catch2::Catch2WithMain
#    bridgeGamestate
#)
#
#target_include_directories(
#    bridgeGamestateTests 
#    PRIVATE 
#    ${CMAKE_SOURCE_DIR}/src
#) 
