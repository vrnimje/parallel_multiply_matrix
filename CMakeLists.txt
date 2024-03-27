cmake_minimum_required(VERSION 3.27)
project(parallel_mul CXX)
find_package(HPX REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main HPX::hpx HPX::wrap_main HPX::iostreams_component)

