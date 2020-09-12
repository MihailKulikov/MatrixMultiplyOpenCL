cmake_minimum_required(VERSION 3.17)
project(MatrixMult C)

set(CMAKE_C_STANDARD 99)

find_package(OpenCL REQUIRED)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kernel.cl
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(MatrixMult main.c loadCLKernel.c func.h)
target_link_libraries(MatrixMult OpenCL::OpenCL)