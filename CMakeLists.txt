cmake_minimum_required(VERSION 3.11.0)

project(a-star-grid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(a-star-grid
    main.cc
)

target_include_directories(a-star-grid PRIVATE .)
target_sources(a-star-grid PRIVATE
    grid.cc
    parsing.cc
    print.cc
    find_path.cc
)