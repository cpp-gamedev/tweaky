project(tweaky-test)

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE
  tweaky::lib
)

if(CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Werror=return-type
  )
endif()

target_sources(${PROJECT_NAME} PRIVATE
  tweaky_test.cpp
)

add_test(NAME tweaky-test COMMAND tweaky-test)
