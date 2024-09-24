
add_subdirectory(Components)
add_subdirectory(Entities)
add_subdirectory(Systems)

add_executable(r-type_client main.cpp r_type.cpp client.cpp)

target_link_libraries(r-type_client PRIVATE Components Entities Systems r-type_interfaces sfml-graphics sfml-window sfml-system)

# Copy the executable to the root directory
add_custom_command(
  TARGET r-type_client
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client>
          ${CMAKE_SOURCE_DIR})
