add_executable(MCTSBridge main.cpp)

add_subdirectory(interfaces)
add_subdirectory(views)
add_subdirectory(models)
#add_subdirectory(controllers)


target_include_directories(MCTSBridge PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(MCTSBridge 
    PRIVATE
        bridgeGamestate
        Boost::json
    )

