cmake_minimum_required(VERSION 3.10)

project(
  R-Type
  VERSION 0.1
  DESCRIPTION "R-Type Game"
  LANGUAGES CXX)

if(LINUX)
  execute_process(COMMAND ./compile.sh)
endif()
if(WIN32)
  execute_process(COMMAND vcpkg integrate install)
  execute_process(COMMAND vcpkg install --triplet x64-windows)
endif()

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (LINUX)
  set(CMAKE_BUILD_TYPE Debug) # set build type to Debug
endif()

# if (UNIX)
#     # Linux-specific settings (by adding a sanitizer)
#     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
#     set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
# endif()

# # Add debug flags
if (LINUX)
  if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb3")
  endif()
endif()

add_subdirectory(Interface)
add_subdirectory(ECS)
add_subdirectory(Client)
add_subdirectory(Server)


########### DOXYGEN ###########

# first we can indicate the documentation build as an option and set it to ON by
# default
option(BUILD_DOC "Build documentation" OFF)

if (BUILD_DOC)
# check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile.in)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

  # request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # note the option ALL which allows to build the docs together with the
  # application
  add_custom_target(
    doc_doxygen ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${MAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM)

  # # Conditionally compile LaTeX to PDF and copy it
  # # Ensure Doxygen and LaTeX are available
  # find_package(LATEX) # This check is optional and serves to ensure Latex is
  #                     # installed
  # if(LATEX_FOUND)
  #   add_custom_command(
  #     TARGET doc_doxygen
  #     POST_BUILD
  #     COMMAND ${CMAKE_COMMAND} -E make_directory
  #             ${CMAKE_CURRENT_SOURCE_DIR}/doc_doxygen/latex
  #     COMMAND ${CMAKE_COMMAND} -E chdir
  #             ${CMAKE_CURRENT_SOURCE_DIR}/doc_doxygen/latex make
  #     COMMAND
  #       ${CMAKE_COMMAND} -E copy
  #       ${CMAKE_CURRENT_SOURCE_DIR}/doc_doxygen/latex/refman.pdf
  #       ${CMAKE_CURRENT_SOURCE_DIR}/Docs
  #       COMMAND
  #       ${CMAKE_COMMAND} -E copy
  #       ${CMAKE_CURRENT_SOURCE_DIR}/doc_doxygen/html
  #       ${CMAKE_CURRENT_SOURCE_DIR}/Docs
  #     COMMENT
  #       "Building PDF documentation with LaTeX and copying to doc directory")
  # else()
  #   message("LaTeX not found, PDF documentation will not be generated.")
  # endif()

else(DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif(DOXYGEN_FOUND)
endif(BUILD_DOC)
