cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS -g)

project(svp)

file(GLOB SRC_LIST src/*.cpp)
message(${SRC_LIST})

add_executable(svp ${SRC_LIST})
# add_library(svp ${SRC_LIST})

