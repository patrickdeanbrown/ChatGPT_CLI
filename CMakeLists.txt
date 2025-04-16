cmake_minimum_required(VERSION 3.15)
project(ChatGPT_CLI)
set(CMAKE_CXX_STANDARD 17)
set(SOURCES
    src/main.cpp
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
find_package(termcolor REQUIRED)
add_executable(chatgpt_cli ${SOURCES} ${HEADERS})
target_link_libraries(chatgpt_cli termcolor::termcolor CURL::libcurl nlohmann_json::nlohmann_json)
