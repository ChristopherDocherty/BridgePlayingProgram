add_library(MCTreeNode
    MCTreeNode.cpp
    MCTreeNode.hpp
)


target_link_libraries(
    MCTreeNode
    PRIVATE
    observerInterface
)

target_include_directories(
    MCTreeNode
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src/interfaces
)





add_subdirectory(bridge)

#Used to insert default config filepaths
configure_file(BridgeMCTreeNode.hpp.in BridgeMCTreeNode.hpp)

add_library(BridgeMCTreeNode 
    ${CMAKE_CURRENT_BINARY_DIR}/BridgeMCTreeNode.hpp
)

target_include_directories(BridgeMCTreeNode PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(BridgeMCTreeNode
    PUBLIC
    MCTreeNode
    BridgeGamestate
)


