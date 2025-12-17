cmake_minimum_required(VERSION 3.10)
project(OS_Lab1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  message("Build for Windows")
  
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
  
  string(REPLACE "/WX" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
  string(REPLACE "/Zi" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif ()

add_executable(child1 src/child1.cpp)
add_executable(child2 src/child2.cpp)
add_executable(parent src/parent.cpp)
