cmake_minimum_required(VERSION 3.10)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(COMMON_LIB_SOURCES
    src/parent.cpp
    src/child.cpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message("Build for Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pthread")
    list(APPEND COMMON_LIB_SOURCES src/os.cpp)

elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message("Build for Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /Zi")
    list(APPEND COMMON_LIB_SOURCES src/os_win.cpp)
endif ()

add_library(common STATIC ${COMMON_LIB_SOURCES})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(parent_process app/main.cpp)
target_link_libraries(parent_process PRIVATE common)

add_executable(child_process app/child_main.cpp)
target_link_libraries(child_process PRIVATE common)