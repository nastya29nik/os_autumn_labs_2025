cmake_minimum_required(VERSION 3.10)
project(OS_Lab3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")

add_library(os_lab_lib STATIC
    src/parent.cpp
    src/child.cpp
    src/os.cpp
)

target_include_directories(os_lab_lib PUBLIC include)

add_executable(parent_process app/main.cpp)
target_link_libraries(parent_process PRIVATE os_lab_lib rt)

add_executable(child_process app/child_main.cpp)
target_link_libraries(child_process PRIVATE os_lab_lib rt)