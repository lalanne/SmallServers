cmake_minimum_required (VERSION 2.8.12)
project (cpp)

add_compile_options(-std=c++11)

include_directories(../)
include_directories(../common/)

add_executable (st 
    ../common/ResponseBuilder.cpp
    ../common/Response.cpp
    ../common/XmlParser.cpp
    server.cpp)

target_link_libraries (st boost_system)


