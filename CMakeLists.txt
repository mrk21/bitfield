cmake_minimum_required(VERSION 2.8)
project(bitfield)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -stdlib=libc++ -Wall -Wextra -Wno-sign-compare")
else()
  set(CMAKE_CXX_FLAGS "-std=gnu++11 -Wall -Wextra -Wno-sign-compare")
endif()

include_directories(${PROJECT_SOURCE_DIR})

if(IS_EXAMPLES)
  add_subdirectory(examples)
else()
  add_subdirectory(test)
endif()
