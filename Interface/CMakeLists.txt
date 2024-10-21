cmake_minimum_required(VERSION 3.10)

project(R-TypeInterfaces
        VERSION 1.0
        DESCRIPTION "Interfaces for the Arcade project"
        LANGUAGES CXX
)

add_library(r-type_interfaces INTERFACE)

target_include_directories(r-type_interfaces
        INTERFACE Include
        hitbox_tmp.hpp
)