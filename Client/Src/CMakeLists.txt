
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

add_subdirectory(Components)
add_subdirectory(Entities)
add_subdirectory(Systems)

add_executable(r-type_client main.cpp r-type_client.cpp client.cpp simpleClient.cpp)

target_compile_features(r-type_client PRIVATE cxx_std_17)

if (MSVC)
  target_link_libraries(r-type_client PRIVATE Components Entities Systems r-type_interfaces r-type_client_interfaces)
else()
  target_compile_options(r-type_client PRIVATE -Wall -Wextra)
  target_link_libraries(r-type_client PRIVATE Components Entities Systems r-type_interfaces r-type_client_interfaces sfml-graphics sfml-window sfml-system)
endif()

# Windows-specific custom command to copy OpenAL DLL for SFML
if(WIN32)
  add_custom_command(
    TARGET r-type_client
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy
      ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
      $<TARGET_FILE_DIR:r-type_client>
    VERBATIM)
endif()

# Copy the executable to the root directory
add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client>
    ${CMAKE_SOURCE_DIR})
