# Server-side project

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(r-type_server main.cpp r_type-server.cpp server.cpp)

target_compile_features(r-type_server PRIVATE cxx_std_17)

add_dependencies(r-type_server r-type_ecs_src)

target_link_libraries(r-type_server r-type_interfaces r-type_server_interfaces r-type_ecs_src r-type_ecs_interfaces)

if(WIN32)
  target_compile_definitions(r-type_server PRIVATE _WIN32)
endif()

# Copy the executable to the root directory
add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server>
          ${CMAKE_SOURCE_DIR})
