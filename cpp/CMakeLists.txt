cmake_minimum_required (VERSION 2.8.11)
project (SmallServer)

#add_subdirectory (Hello)
#add_subdirectory (Demo)

add_library (server server.cpp)
#target_include_directories (Hello PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#add_executable (helloDemo demo.cxx demo_b.cxx)
#target_link_libraries (helloDemo LINK_PUBLIC Hello)


