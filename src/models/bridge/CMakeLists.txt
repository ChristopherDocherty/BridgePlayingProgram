add_library(bridgeGamestate
    utils/bridgeUtils.hpp
    utils/bridgeUtils.cpp
    bridgeCard.hpp
    bridgeCard.cpp 
    bridgeGamestate.hpp
    bridgeGamestate.cpp
    bridgeGamestateLoader.hpp
    bridgeGamestateLoader.cpp
)

target_link_libraries(bridgeGamestate 
    PRIVATE
      tl::expected
      nlohmann_json::nlohmann_json
      fmt::fmt
    )

target_include_directories(bridgeGamestate
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
