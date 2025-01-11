cmake_minimum_required(VERSION 3.10)

project(PartialSum)

set(CMAKE_C_STANDARD 99)

find_package(OpenMP REQUIRED)

add_executable(main main.c)

target_link_libraries(main m OpenMP::OpenMP_C)

if(OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()