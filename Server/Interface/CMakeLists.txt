cmake_minimum_required(VERSION 3.10)

project(R-TypeServerInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the Server Arcade project"
        LANGUAGES CXX
)

add_library(r-type_server_interfaces INTERFACE)

target_include_directories(r-type_server_interfaces
        INTERFACE Include
)
