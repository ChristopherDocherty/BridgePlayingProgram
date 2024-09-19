cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(MCTSBridge  VERSION 1.0
                    DESCRIPTION "Bridge MCTS files"
                    LANGUAGES CXX)

if(MSVC)
  add_compile_options( /W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

find_package(fmt CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(tl-expected CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

#Saving the dir of config files for later substition
#set(CONFIG_BINARY_DIR "${CMAKE_BINARY_DIR}/config")
#add_subdirectory(config)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

