add_library(range-v3
INTERFACE
)

target_include_directories(range-v3 INTERFACE . .. ../..)

set_target_properties(range-v3 PROPERTIES LINKER_LANGUAGE CXX)
