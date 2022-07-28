include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
    converterTests 
    converterTests.cc
)

target_link_libraries(
    converterTests 
    GTest::gtest_main
    bridgeGamestate
)

target_include_directories(
    converterTests
    PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
) 


include(GoogleTest)
gtest_discover_tests(converterTests)
