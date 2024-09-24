# Client-side project
project(Client VERSION 0.1)

include_directories(${PROJECT_SOURCE_DIR}/Include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(r-type_client Src/main.cpp Src/r_type.cpp Src/client.cpp)

target_link_libraries(r-type_client PRIVATE r-type_interfaces sfml-graphics
                                            sfml-window sfml-system)
target_compile_features(r-type_client PRIVATE cxx_std_17)

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
