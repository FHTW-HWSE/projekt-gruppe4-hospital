cmake_minimum_required(VERSION 3.10) 
project(myHospital)

set(CMAKE_C_STANDARD 99) 

include_directories(include) 


set(SOURCE_FILES
        src/main.c
        src/functions.c
)

add_executable(myHospital ${SOURCE_FILES})

# Clean command to be added in the custom targets
set_property(DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/Makefile"
    "${CMAKE_CURRENT_BINARY_DIR}/myHospital")
