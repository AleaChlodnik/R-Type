
add_library(r-type_ecs_src
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
  target_link_libraries(r-type_ecs_src PRIVATE r-type_ecs_interfaces r-type_interfaces)
else()
  target_compile_options(r-type_ecs_src PRIVATE -Wall -Wextra)
  target_link_libraries(r-type_ecs_src PRIVATE r-type_ecs_interfaces r-type_interfaces sfml-graphics sfml-window sfml-system)
endif()


if(WIN32)
  add_custom_command(
    TARGET r-type_ecs_src
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:r-type_ecs_src>
    VERBATIM)
endif()
