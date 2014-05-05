cmake_minimum_required(VERSION 2.8)
project(bitfield2)

set(CMAKE_CXX_FLAGS "-std=gnu++11 -stdlib=libc++ -Wall -Wextra -Wno-sign-compare")

include_directories(${PROJECT_SOURCE_DIR})

if(IS_EXAMPLES)
  add_subdirectory(examples)
else()
  add_subdirectory(test)
endif()
