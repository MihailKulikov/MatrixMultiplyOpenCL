cmake_minimum_required(VERSION 3.17)
project(MatrixMult C)

set(CMAKE_C_STANDARD 99)

find_package(OpenCL REQUIRED)
configure_file(src/kernel.cl
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(MatrixMult src/main.c src/loadCLKernel.c src/initializeOpenCL.c src/multiplyMatrix.c TestFramework/CuTest.c TestFramework/CuTest.h Tests/testMatrixMultiply.c Tests/AllTests.c src/getTransitiveClosure.c Tests/testGetTransitiveClosure.c)
target_link_libraries(MatrixMult OpenCL::OpenCL)