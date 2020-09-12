#include <stdio.h>
#include <CL/cl.h>
#include "func.h"

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

char *matrixMultiply(const char *first_matrix, const char *second_matrix, int matrix_order){
    cl_int err;
    size_t matrix_size = matrix_order * matrix_order;
    char *result = malloc(matrix_size);
    cl_mem first_matrix_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, matrix_size, NULL, &err);
    cl_mem second_matrix_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, matrix_size, NULL, &err);
    cl_mem result_matrix_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, matrix_size, NULL, &err);
    if (err != CL_SUCCESS){
        printf("Error: Failed to allocate device memory!\n");
        exit(1);
    }

    err = clEnqueueWriteBuffer(commandQueue, first_matrix_buffer, CL_FALSE, 0, matrix_size, (void *)first_matrix, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(commandQueue, second_matrix_buffer, CL_FALSE, 0, matrix_size, (void *) second_matrix, 0, NULL, NULL);
    if (err != CL_SUCCESS){
        printf("Error: Failed clEnqueueWriteBuffer");
        exit(1);
    }

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &result_matrix_buffer);
    err = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &first_matrix_buffer);
    err = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *) &second_matrix_buffer);
    err = clSetKernelArg(kernel, 3, sizeof(int), (void *)&matrix_order);
    if(err != CL_SUCCESS){
        printf("Error: Failed clSetKernelArg");
        exit(1);
    }

    const size_t global_work_size[] = {(size_t)matrix_order, (size_t)matrix_order};
    err = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    err = clEnqueueReadBuffer(commandQueue, result_matrix_buffer, CL_TRUE, 0, matrix_size, result, 0, NULL, NULL);
    if (err != CL_SUCCESS){
        printf("\"Error: Failed to execute kernel! %d\n", err);
        exit(1);
    }

    return result;
}

int main() {
    cl_int error;
    cl_platform_id platformIds[1];
    error = clGetPlatformIDs(1, platformIds, NULL);
    if (error != CL_SUCCESS){
        printf("Fail clGetPlatformIDs");
        return EXIT_FAILURE;
    }

    cl_device_id deviceIDs[1];
    error = clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, 1, deviceIDs, NULL);
    if (error != CL_SUCCESS){
        printf("Fail clGetDeviceIDs");
        return EXIT_FAILURE;
    }

    const cl_context_properties properties [] ={
            CL_CONTEXT_PLATFORM,
            (cl_context_properties)platformIds[0], 0
    };
    context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &error);
    if (error != CL_SUCCESS){
        printf("Fail clCreateContextFromType");
        return EXIT_FAILURE;
    }

    commandQueue = clCreateCommandQueue(context, deviceIDs[0], 0, &error);
    if (error != CL_SUCCESS){
        printf("Fail clCreateCommandQueue");
        return EXIT_FAILURE;
    }

    char *kernelSource;
    long fileSize = loadCLKernel("kernel.cl", &kernelSource);
    if (fileSize < 0L){
        perror("File read failed");
        return EXIT_FAILURE;
    }

    cl_program program = clCreateProgramWithSource(context, 1, (const char **) &kernelSource, NULL, &error);
    free(kernelSource);
    if (error != CL_SUCCESS){
        printf("Fail clCreateProgramWithSource");
        return EXIT_FAILURE;
    }
    if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS){
        printf("Fail clBuildProgram");
        return EXIT_FAILURE;
    }

    kernel = clCreateKernel(program, "matrixMult", &error);
    if (error != CL_SUCCESS){
        printf("Fail clCreateKernel");
        return EXIT_FAILURE;
    }

    char A[4] = {0, 0, 1, 0};
    char B[4] = {0, 1, 0, 1};
    char matrix_order = 2;
    char *result = matrixMultiply(A, B, matrix_order);
    for (int i = 0; i < 4; i++){
        printf("%i ", result[i]);
    }

    return 0;
}
