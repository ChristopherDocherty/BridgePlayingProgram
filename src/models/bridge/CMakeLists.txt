add_library(bridgeGamestate
    bridgeGamestate.cpp
    bridgeGamestate.hpp
)

add_library(bridgeCard
    bridgeCard.cpp 
    bridgeCard.hpp
)

add_subdirectory(utils)

target_link_libraries(bridgeCard
    PRIVATE
        utils
    )


target_link_libraries(bridgeGamestate 
    PRIVATE
        bridgeCard
        utils
    )

