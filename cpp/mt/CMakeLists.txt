cmake_minimum_required (VERSION 2.8.12)
project (cpp)

add_compile_options(-std=c++11)

include_directories(../)
include_directories(../common/)

add_executable (mt 
    server.cpp
    ../common/ResponseBuilder.cpp
    ../common/Response.cpp
    ../common/XmlParser.cpp
    )

set(CMAKE_EXE_LINKER_FLAGS -pthread)

target_link_libraries (mt boost_system)


