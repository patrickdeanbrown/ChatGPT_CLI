cmake_minimum_required(VERSION 3.15)
project(ChatGPT_CLI)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    src/chatgptapi.cpp
    src/chathistory.cpp
    src/command.cpp
    src/commandcontext.cpp
    src/filereadwrite.cpp
    src/formatting.cpp
    src/request.cpp
    src/apikeycheck.cpp
)

set(HEADERS
    src/chatgptapi.hpp
    src/chathistory.hpp
    src/command.hpp
    src/commandcontext.hpp
    src/filereadwrite.hpp
    src/formatting.hpp
    src/request.hpp
)

find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)
# find_package(termcolor REQUIRED) # Removed: termcolor is now a subdirectory
# add_subdirectory(external/termcolor) # Removed

# Build static library from all code except main.cpp
add_library(chatgpt_cli_lib STATIC ${SOURCES} ${HEADERS})
target_include_directories(chatgpt_cli_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)
# target_link_libraries(chatgpt_cli_lib termcolor::termcolor CURL::libcurl nlohmann_json::nlohmann_json) # termcolor removed
target_link_libraries(chatgpt_cli_lib CURL::libcurl nlohmann_json::nlohmann_json) # termcolor removed

# CLI executable links to the library
add_executable(chatgpt_cli src/main.cpp)
target_link_libraries(chatgpt_cli 
    PRIVATE chatgpt_cli_lib
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
)

# --- GoogleTest Setup ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE) # Recommended by FTXUI to avoid re-fetching on every configure
FetchContent_Declare(ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
    GIT_TAG v6.1.9 # Use a specific tag for version consistency
)
FetchContent_MakeAvailable(ftxui)

# Add FTXUI include directory to the chatgpt_cli target
target_include_directories(chatgpt_cli PRIVATE ${ftxui_SOURCE_DIR}/include)

enable_testing()

file(GLOB TEST_SOURCES tests/*.cpp)
add_executable(unit_tests ${TEST_SOURCES})
target_link_libraries(unit_tests gtest_main chatgpt_cli_lib)
target_include_directories(unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME unit_tests COMMAND unit_tests)
