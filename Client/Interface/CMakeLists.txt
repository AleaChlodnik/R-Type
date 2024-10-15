cmake_minimum_required(VERSION 3.10)

project(R-TypeClientInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the Client R-type project"
        LANGUAGES CXX
)

add_library(r-type_client_interfaces INTERFACE)

target_include_directories(r-type_client_interfaces
        INTERFACE Include r-type_ecs_interfaces
)