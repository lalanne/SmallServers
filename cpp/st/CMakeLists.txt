cmake_minimum_required (VERSION 2.8.12)
project (cpp)

add_compile_options(-std=c++11)

add_executable (st server.cpp)

target_link_libraries (st boost_system)


