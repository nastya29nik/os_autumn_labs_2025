cmake_minimum_required(VERSION 3.10)
project(Threads)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

add_library(thread_lib src/thread.cpp)

target_include_directories(thread_lib PUBLIC include)

add_executable(main main.cpp)
target_link_libraries(main thread_lib)