add_subdirectory(utils)

add_library(bridgeCard
    bridgeCard.hpp
    bridgeCard.cpp 
)

target_link_libraries(bridgeCard
    PRIVATE
        utils
    )

add_library(bridgeGamestate
    bridgeGamestate.hpp
    bridgeGamestate.cpp
    bridgeGamestateLoader.hpp
    bridgeGamestateLoader.cpp
)

target_link_libraries(bridgeGamestate 
    PRIVATE
        bridgeCard
        utils
        json
    )

target_include_directories(bridgeGamestate
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

#TODO: consider the implications of linking the utils library twice, could this lead to 2 instances of the singleton?
#Might not technically matter here but owrht understanding
