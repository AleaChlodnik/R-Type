# Client-side project
project(Client VERSION 0.1)

include_directories(${PROJECT_SOURCE_DIR}/Include)

# Collect client source files
file(GLOB_RECURSE CLIENT_SOURCES
    ${PROJECT_SOURCE_DIR}/Src/*.cpp
)

add_executable(r-type_client ${CLIENT_SOURCES})

target_link_libraries(r-type_client PRIVATE sfml-graphics sfml-window sfml-system)

target_compile_features(r-type_client PRIVATE cxx_std_17)

# Set output directory for client binary
set_target_properties(r-type_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/Client
)

# Windows-specific custom command to copy OpenAL DLL for SFML
if(WIN32)
    add_custom_command(
        TARGET r-type_client
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:r-type_client>
        VERBATIM
    )
endif
