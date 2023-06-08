project(whackx)

include(FetchContent)

FetchContent_Declare(gvdi
  GIT_REPOSITORY https://github.com/karnkaul/gvdi
  GIT_TAG 5566d28
)

FetchContent_MakeAvailable(gvdi)

set(WHACKX_INSPECTOR "DEBUG_ONLY" CACHE STRING "Enable whackx inspector [DEBUG_ONLY | ALWAYS | NEVER]")

set(inspector_define "WHACKX_INSPECTOR")

if("${WHACKX_INSPECTOR}" STREQUAL "NEVER")
  set(inspector_define "")
elseif("${WHACKX_INSPECTOR}" STREQUAL "DEBUG_ONLY")
  set(inspector_define $<$<CONFIG:Debug>:WHACKX_INSPECTOR>)
endif()

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  tweaky::lib
  gvdi::gvdi
)

target_include_directories(${PROJECT_NAME} PRIVATE
  .
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
  $<$<CONFIG:Debug>:WHACKX_DEBUG>
  ${inspector_define}
)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
  )
endif()

target_sources(${PROJECT_NAME} PRIVATE
  whackx/app.cpp
  whackx/app.hpp
  whackx/defines.hpp
  whackx/game.cpp
  whackx/game.hpp
  whackx/io.cpp
  whackx/io.hpp
  main.cpp
)
