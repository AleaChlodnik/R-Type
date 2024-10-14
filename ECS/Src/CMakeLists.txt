
add_library(r-type_ecs_src)

target_include_directories(r-type_ecs_src PRIVATE r-type_ecs_interfaces)

target_sources(r-type_ecs_src PRIVATE
        Entities/entity_factory.cpp
        Systems/render_system.cpp
        Systems/update_system.cpp
)
