configure_file(../models/bridge/testBoards.json .)

add_executable( bridgeTerminalViewTests 
    bridgeTerminalViewTests.cc
)

target_link_libraries(
    bridgeTerminalViewTests 
    PUBLIC
    bridgeTerminalView
    Catch2::Catch2WithMain
    bridgeGamestate
    PRIVATE
    range-v3
)

target_include_directories(
    bridgeTerminalViewTests 
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
) 

include(CTest)
include(Catch)
catch_discover_tests(bridgeTerminalViewTests)
