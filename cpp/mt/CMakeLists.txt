cmake_minimum_required (VERSION 2.8.12)
project (cpp)

add_compile_options(-std=c++11)

add_executable (mt server.cpp)

set(CMAKE_EXE_LINKER_FLAGS -pthread)

target_link_libraries (mt boost_system)


