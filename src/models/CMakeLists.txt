add_library(MCTreeNode
    MCTreeNode.cpp
    MCTreeNode.hpp
)


target_link_libraries(
    MCTreeNode
    PUBLIC
    observerInterface
)

target_include_directories(
    MCTreeNode
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)




add_subdirectory(bridge)

#Used to insert default config filepaths
configure_file(bridgeMCTreeNode.hpp.in bridgeMCTreeNode.hpp)

add_library(
    bridgeMCTreeNode 
    ${CMAKE_CURRENT_BINARY_DIR}/bridgeMCTreeNode.hpp
    bridgeMCTreeNode.cpp
)

target_include_directories(
    bridgeMCTreeNode 
    PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(bridgeMCTreeNode
    PUBLIC
    MCTreeNode
    bridgeGamestate
    Boost::json
)


