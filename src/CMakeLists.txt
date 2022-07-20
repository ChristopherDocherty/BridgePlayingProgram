add_executable(MCTSBridge main.cpp)

add_subdirectory(bridge)


target_link_libraries(MCTSBridge 
    PRIVATE
        bridgeGamestate
    )

