cmake_minimum_required(VERSION 3.23)
project(test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp functions.cpp test_loading_functions.cpp test_moving_patients_functions.cpp test_add_patient.cpp)

add_executable(test ${SOURCE_FILES})
