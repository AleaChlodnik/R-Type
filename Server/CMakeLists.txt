# Server-side project
project(Server VERSION 0.1)

include_directories(${PROJECT_SOURCE_DIR}/R-Type/ Include)

add_executable(r-type_server Src/main.cpp)
# target_link_libraries(r-type_server PRIVATE sfml-graphics sfml-window
# sfml-system)
target_compile_features(r-type_server PRIVATE cxx_std_17)

target_link_libraries(r-type_server r-type_interfaces)
if(WIN32)
  target_compile_definitions(r-type_server PRIVATE _WIN32)
endif()

# Copy the executable to the root directory
add_custom_command(
  TARGET r-type_server
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_server>
          ${CMAKE_SOURCE_DIR})
