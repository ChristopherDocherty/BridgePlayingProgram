add_library(bridgeTerminalView
    bridgeTerminalView.cpp
    viewUtils.cpp
)


target_link_libraries(
    bridgeTerminalView
    PUBLIC
    bridgeGamestate
    PRIVATE
    range-v3
)

target_include_directories(
    bridgeTerminalView
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)




