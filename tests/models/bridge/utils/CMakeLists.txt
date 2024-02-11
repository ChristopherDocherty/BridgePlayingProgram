add_executable(
    converterTests 
    converterTests.cc
)

target_link_libraries(
    converterTests 
    Catch2::Catch2WithMain
    utils 
)

target_include_directories(
    converterTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 

include(CTest)
include(Catch)
catch_discover_tests(converterTests)
