

add_library(bridge
    bridgeCard.cpp 
    bridgeCard.h
)

add_subdirectory(utils)

target_link_libraries(bridge 
    PRIVATE
        utils
    )

