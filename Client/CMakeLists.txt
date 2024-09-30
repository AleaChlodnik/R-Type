project(Client VERSION 0.1)

add_subdirectory(Interface)
add_subdirectory(Src)

# Windows-specific custom command to copy OpenAL DLL for SFML
# if(WIN32)
#   add_custom_command(
#     TARGET r-type_client
#     COMMENT "Copy OpenAL DLL"
#     PRE_BUILD
#     COMMAND
#       ${CMAKE_COMMAND} -E copy
#       ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
#       $<TARGET_FILE_DIR:r-type_client>
#     VERBATIM)
# endif()