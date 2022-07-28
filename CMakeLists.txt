cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)

project(MCTSBridge  VERSION 1.0
                    DESCRIPTION "Bridge MCTS files"
                    LANGUAGES CXX)


add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
