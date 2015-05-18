# project
project(assembler CXX C)

cmake_minimum_required(VERSION 3.0)

# function cxx_executable
function(my_cxx_executable name ${ARGN})
  add_executable(${name} ${ARGN})

  if (cxx_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}")
  endif()

  if (c_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}")
  endif()

 target_link_libraries(${name} pthread)# gtest gtest_main )
endfunction(my_cxx_executable)


# building flags and compiler
set(c_flags "-g -Wall -Wshadow -march=native ")
set(cxx_flags "${c_flags}  -std=c++11")


# building flags and compiler
#set(c_base_flags "-g -Wall -Wshadow -march=native")
#set(cxx_base_flags "${c_flags} -fno-exception")

# env setting
set(PROJECT_TOP_DIR ${CMAKE_SOURCE_DIR} CACHE PATH "project top dir")
set(PROJECT_BUILD_DIR ${PROJECT_TOP_DIR}/build CACHE PATH "build dir")
set(PROJECT_OUT_DIR ${PROJECT_TOP_DIR}/out CACHE PATH "out lib.so lib.a exe dir")
# add output directory to link path
add_definitions(-L${PROJECT_OUT_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR} CACHE PATH "lib*.a dir")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR} CACHE PATH "lib*.so dir")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_OUT_DIR} CACHE PATH "execuable dir")

my_cxx_executable(vmtranslator vmtranslator.cpp
  codeWriter.cpp
  parser.cpp)

target_link_libraries(vmtranslator boost_program_options boost_system boost_filesystem)
