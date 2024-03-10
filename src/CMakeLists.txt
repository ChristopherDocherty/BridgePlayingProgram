add_subdirectory(models)
add_subdirectory(includes)
add_subdirectory(views)
#add_subdirectory(interfaces)
#add_subdirectory(controllers)

add_executable(main main.cpp)

target_include_directories(main PRIVATE)

target_link_libraries(main
    PRIVATE
        bridgeGamestate
        bridgeTerminalView
        range-v3
    )

configure_file(../tests/models/bridge/testBoards.json .)
