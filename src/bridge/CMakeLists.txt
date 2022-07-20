add_library(bridgeGamestate
    bridgeGamestate.cpp
    bridgeGamestate.h
)

add_library(bridgeCard
    bridgeCard.cpp 
    bridgeCard.h
)

add_subdirectory(utils)

target_link_libraries(bridgeGamestate 
    PRIVATE
        bridgeCard
        utils
    )

