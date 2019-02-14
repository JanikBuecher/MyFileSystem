cmake_minimum_required(VERSION 3.13)
project(MyFileSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyFileSystem CMakeLists.txt FileSystem.c)
