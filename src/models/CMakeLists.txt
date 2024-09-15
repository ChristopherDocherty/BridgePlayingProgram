add_subdirectory(bridge)

add_library(MCTree
    MCTree.cpp
    MCTreeNode.cpp
    bridgeMctsFacade.cpp
)


target_link_libraries(MCTree
    PUBLIC
    range-v3
)

target_include_directories(MCTree
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)

