cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(MCTSBridge  VERSION 1.0
                    DESCRIPTION "Bridge MCTS files"
                    LANGUAGES CXX)

if(MSVC)
  add_compile_options( /W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()




set(Boost_USE_DEBUG_LIBS        OFF)
set(Boost_USE_RELEASE_LIBS       ON)
find_package(Boost REQUIRED COMPONENTS json) 


#Saving the dir of config files for later substition
set(CONFIG_BINARY_DIR "${CMAKE_BINARY_DIR}/config")
add_subdirectory(config)

if(Boost_FOUND)

    add_subdirectory(src)

    enable_testing()
    
    add_subdirectory(tests)
    
endif()







