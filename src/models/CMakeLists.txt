add_subdirectory(bridge)

add_library(MCTree
    MCTree.hpp
    MCTree.cpp
    MCTreeNode.cpp
    MCTreeNode.hpp
)


target_link_libraries(
    MCTree
    PUBLIC
    observerInterface
    PRIVATE
    range-v3
)

target_include_directories(
    MCTree
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
)



#Used to insert default config filepaths
#configure_file(bridgeMCTreeNode.hpp.in bridgeMCTreeNode.hpp)
#
#add_library(
#    bridgeMCTreeNode 
#    ${CMAKE_CURRENT_BINARY_DIR}/bridgeMCTreeNode.hpp
#    bridgeMCTreeNode.cpp
#)
#
#target_include_directories(
#    bridgeMCTreeNode 
#    PUBLIC 
#    ${CMAKE_CURRENT_BINARY_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}
#    ${Boost_INCLUDE_DIRS}
#)
#
#target_link_libraries(bridgeMCTreeNode
#    PUBLIC
#    MCTreeNode
#    bridgeGamestate
#    Boost::json
#)
