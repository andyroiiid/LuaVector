cmake_minimum_required(VERSION 3.24)
project(LuaVector)

add_subdirectory(lua EXCLUDE_FROM_ALL)

set(CMAKE_CXX_STANDARD 17)

add_executable(Demo main.cpp LuaVector.cpp LuaVector.h)

target_link_libraries(Demo lua)
