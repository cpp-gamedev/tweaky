include(FetchContent)

FetchContent_Declare(djson
  GIT_REPOSITORY https://github.com/karnkaul/djson
  GIT_TAG c8e8a0c
)
FetchContent_MakeAvailable(djson)

add_library(${PROJECT_NAME})
add_library(tweaky::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)

target_link_libraries(${PROJECT_NAME} PUBLIC
  djson::djson
)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
  )
endif()

target_sources(${PROJECT_NAME} PRIVATE
  include/tweaky/data_io.hpp
  include/tweaky/data.hpp
  include/tweaky/database.hpp
  include/tweaky/inspector.hpp
  include/tweaky/value.hpp

  src/database.cpp
)
