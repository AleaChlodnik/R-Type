cmake_minimum_required(VERSION 3.10)

project(R-TypeECSInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the ECS R-type project"
        LANGUAGES CXX
)

add_library(r-type_ecs_interfaces INTERFACE)

target_include_directories(r-type_ecs_interfaces
        INTERFACE Include r-type_interfaces
)
