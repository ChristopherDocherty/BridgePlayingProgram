add_executable(MCTSBridge main.cpp)

add_subdirectory(utils)


target_link_libraries(MCTSBridge 
    PRIVATE
        utils    
    )

