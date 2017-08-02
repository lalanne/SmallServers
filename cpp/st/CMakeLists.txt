cmake_minimum_required (VERSION 2.8.12)
project (SmallServer)

add_compile_options(-std=c++11)

add_executable (server 
    response.cpp
    server.cpp)

target_link_libraries (server boost_system)


