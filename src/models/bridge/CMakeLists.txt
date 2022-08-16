add_subdirectory(utils)


add_library(bridgeGamestate
    bridgeGamestate.cpp
    bridgeGamestate.hpp
)

add_library(bridgeCard
    bridgeCard.cpp 
    bridgeCard.hpp
)


target_link_libraries(bridgeCard
    PRIVATE
        utils
    )

#TODO: check boost stuff works without gcc auto includes

target_link_libraries(bridgeGamestate 
    PRIVATE
        bridgeCard
        utils
        Boost::json
    )

#TODO: consider the implications of linking the utils library twice, could this lead to 2 instances of the singleton?
#Might not technically matter here but owrht understanding
