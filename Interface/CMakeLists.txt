cmake_minimum_required(VERSION 3.10)

project(R-TypeInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the Arcade project"
        LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
        asiocmake
        GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
        GIT_TAG        "main"
)
FetchContent_MakeAvailable(asiocmake)

add_library(r-type_interfaces INTERFACE)

target_include_directories(r-type_interfaces
        INTERFACE Include
)

target_link_libraries(r-type_interfaces
        INTERFACE asio::asio
)