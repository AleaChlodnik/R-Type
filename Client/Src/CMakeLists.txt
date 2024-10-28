
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Optional: Set for each configuration (if using multi-configuration generators)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_BINARY_DIR}/bin)

add_executable(r-type_client main.cpp scenes.cpp)

add_dependencies(r-type_client r-type_ecs_src)

if (MSVC)
  target_link_libraries(r-type_client PRIVATE r-type_interfaces r-type_client_interfaces r-type_ecs_src r-type_ecs_interfaces sfml-graphics sfml-window sfml-system)
else()
  target_compile_options(r-type_client PRIVATE -Wall -Wextra)
  target_link_libraries(r-type_client PRIVATE r-type_interfaces r-type_client_interfaces r-type_ecs_src r-type_ecs_interfaces sfml-graphics sfml-window sfml-system)
endif()

# Copy the executable to the root directory
add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client>
    ${CMAKE_SOURCE_DIR})
