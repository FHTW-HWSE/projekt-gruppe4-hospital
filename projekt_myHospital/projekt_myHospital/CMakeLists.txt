cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp functions.c)

add_executable(test main.cpp functions.c functions.h)

set_source_files_properties(functions.c PROPERTIES LANGUAGE C)
