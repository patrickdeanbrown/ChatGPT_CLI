cmake_minimum_required(VERSION 3.10)
project(termcolor CXX)

add_library(termcolor INTERFACE)
add_library(termcolor::termcolor ALIAS termcolor)

target_include_directories(termcolor INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>  # Adjust if you have an install step
)

# If termcolor.hpp is in a subdirectory like 'include' within external/termcolor:
# target_include_directories(termcolor INTERFACE
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#     $<INSTALL_INTERFACE:include>
# )
