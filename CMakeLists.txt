cmake_minimum_required(VERSION 3.27)
project(parallel_mul CXX)
find_package(HPX REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main HPX::hpx HPX::wrap_main HPX::iostreams_component)
find_package(Doxygen OPTIONAL_COMPONENTS dot)
if (DOXYGEN_FOUND)
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
  doxygen_add_docs(doc
    ${CMAKE_SOURCE_DIR}
  )
endif(DOXYGEN_FOUND)

