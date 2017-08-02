cmake_minimum_required (VERSION 2.8.12)
project (cpp)

add_compile_options(-std=c++11)

include_directories(../)

add_executable (st 
    ../response.cpp
    server.cpp)

target_link_libraries (st boost_system)


