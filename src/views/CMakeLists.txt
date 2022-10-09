add_library(viewUtils
    viewUtils.hpp
    viewUtils.cpp
)

add_library(bridgeTerminalView
    bridgeTerminalView.hpp
    bridgeTerminalView.cpp
)


target_link_libraries(
    bridgeTerminalView
    PUBLIC
    viewUtils
    observerInterface
    Boost::json
)

target_include_directories(
    bridgeTerminalView
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${Boost_INCLUDE_DIRS}
)




