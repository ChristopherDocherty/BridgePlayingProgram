add_executable(MCTSBridge main.cpp)

add_subdirectory(interfaces)
add_subdirectory(models)


target_link_libraries(MCTSBridge 
    PRIVATE
        bridgeGamestate
    )

