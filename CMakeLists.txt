cmake_minimum_required(VERSION 3.10)

project(
    R-Type
    VERSION 0.1
    DESCRIPTION "R-Type Game"
    LANGUAGES CXX)

add_library(arcade_interfaces INTERFACE)

target_include_directories(arcade_interfaces
        INTERFACE include
)

if(LINUX)
    execute_process(COMMAND ./compile.sh)
endif()
# if(WIN32)
#     ./compile.bat
# endif()

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Interface)
add_subdirectory(Client)
add_subdirectory(Server)
