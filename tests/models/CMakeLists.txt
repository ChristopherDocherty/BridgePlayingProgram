add_subdirectory(bridge)

add_executable( MCTreeNodeTests
    MCTreeNodeTests.cc
)

target_link_libraries( MCTreeNodeTests
    Catch2::Catch2WithMain
    MCTree
)

target_include_directories(MCTreeNodeTests
    PUBLIC
    ${CMAKE_BINARY_DIR}/src
) 
