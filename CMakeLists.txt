cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(MCTSBridge  VERSION 1.0
                    DESCRIPTION "Old Bridge MCTS files"
                    LANGUAGES CXX)


include_directories(${PROJECT_SOURCE_DIR})

#add_library(MCTS  STATIC MCTS.h)
add_library(Bridge STATIC Bridge.cpp Bridge.h)


add_executable(MCTSBridge  bridge_MCTS.cpp)

target_link_libraries(MCTSBridge Bridge)

