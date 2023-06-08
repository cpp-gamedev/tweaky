cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "-d")

project(tweaky)

set(is_root_project OFF)

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(is_root_project ON)
endif()

add_subdirectory(tweaky)

option(TWEAKY_WHACKX "Build whackx (game using tweaky)" ${is_root_project})
option(TWEAKY_TEST "Build test" ${is_root_project})

if(TWEAKY_WHACKX)
  add_subdirectory(whackx)
endif()

if(TWEAKY_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
