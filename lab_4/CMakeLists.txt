cmake_minimum_required(VERSION 3.10)
project(OS_Lab4)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -fPIC")

include_directories(include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_library(impl1 SHARED src/lib1.c)
target_link_libraries(impl1 m)

add_library(impl2 SHARED src/lib2.c)

add_executable(prog1 src/prog1.c)
target_link_libraries(prog1 impl1 m)
set_target_properties(prog1 PROPERTIES INSTALL_RPATH "$ORIGIN/../lib")
set_target_properties(prog1 PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)

add_executable(prog2 src/prog2.c src/os.c)
target_link_libraries(prog2 dl)
add_dependencies(prog2 impl1 impl2)