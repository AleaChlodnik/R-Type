
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

add_subdirectory(Components)
add_subdirectory(Entities)
add_subdirectory(Systems)

add_executable(r-type_client main.cpp r_type.cpp tools.cpp client.cpp)

target_link_libraries(r-type_client PRIVATE Components Entities Systems r-type_interfaces sfml-graphics sfml-window sfml-system)

target_include_directories(r-type_client PRIVATE
    "${PROJECT_SOURCE_DIR}/Include"
    "${PROJECT_SOURCE_DIR}/Include/Components"
    "${PROJECT_SOURCE_DIR}/Include/Entities"
    "${PROJECT_SOURCE_DIR}/Include/Systems"
)

target_compile_features(r-type_client PRIVATE cxx_std_17)
target_compile_options(r-type_client PRIVATE -Wall -Wextra)

# Copy the executable to the root directory
add_custom_command(
    TARGET r-type_client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:r-type_client>
    ${CMAKE_SOURCE_DIR})
