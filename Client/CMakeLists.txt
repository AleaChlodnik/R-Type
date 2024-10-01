project(Client VERSION 0.1)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL SYSTEM)
FetchContent_MakeAvailable(SFML)

add_subdirectory(Interface)
add_subdirectory(Src)
