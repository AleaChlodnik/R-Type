
add_library(r-type_ecs_src STATIC
        Entities/entity_factory.cpp
        Systems/render_system.cpp
        Systems/update_system.cpp
        Systems/animation_system.cpp
        Systems/move_system.cpp
        Systems/collision_system.cpp
        hitbox_tmp.cpp
        sprite_path.cpp
        a_scenes.cpp
)


if (MSVC)
  target_link_libraries(r-type_ecs_src PRIVATE r-type_ecs_interfaces r-type_interfaces sfml-graphics sfml-window sfml-system)
else()
  target_compile_options(r-type_ecs_src PRIVATE -Wall -Wextra)
  target_link_libraries(r-type_ecs_src PRIVATE r-type_ecs_interfaces r-type_interfaces sfml-graphics sfml-window sfml-system)
endif()

