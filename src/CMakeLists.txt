add_subdirectory(models)
add_subdirectory(views)

add_library(BridgeController
  BridgeController.cpp
)

target_link_libraries(BridgeController 
  bridgeGamestate
  bridgeTerminalView
  MCTree
)

target_include_directories(BridgeController
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)


add_executable(main main.cpp)

target_include_directories(main PRIVATE .) 

target_link_libraries(main
    PRIVATE
      BridgeController 
      bridgeGamestate
      bridgeTerminalView
      range-v3
    )

configure_file(../tests/models/bridge/testBoards.json .)
