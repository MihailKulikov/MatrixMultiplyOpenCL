#include <CL/cl.h>
#include <stdio.h>

extern cl_context context;
extern cl_command_queue commandQueue;
extern cl_kernel kernel;

void *multiplyMatrix(char *result, const char *first_matrix, const char *second_matrix, int matrix_order) {
    cl_int err;
    size_t matrix_size = matrix_order * matrix_order;
    cl_mem first_matrix_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, matrix_size, NULL, &err);
    cl_mem second_matrix_buffer = clCreateBuffer(context, CL_MEM_READ_ONLY, matrix_size, NULL, &err);
    cl_mem result_matrix_buffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY, matrix_size, NULL, &err);
    if (!first_matrix_buffer || !second_matrix_buffer || !result_matrix_buffer) {
        printf("Error: Failed to allocate device memory!\n");
        exit(1);
    }

    err = clEnqueueWriteBuffer(commandQueue, first_matrix_buffer, CL_FALSE, 0, matrix_size, (void *) first_matrix, 0,
                               NULL, NULL);
    err |= clEnqueueWriteBuffer(commandQueue, second_matrix_buffer, CL_FALSE, 0, matrix_size, (void *) second_matrix, 0,
                                NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed clEnqueueWriteBuffer");
        exit(1);
    }

    err = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &result_matrix_buffer);
    err |= clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &first_matrix_buffer);
    err |= clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *) &second_matrix_buffer);
    err |= clSetKernelArg(kernel, 3, sizeof(int), (void *) &matrix_order);
    if (err != CL_SUCCESS) {
        printf("Error: Failed clSetKernelArg");
        exit(1);
    }

    const size_t global_work_size[] = {(size_t) matrix_order, (size_t) matrix_order};
    err = clEnqueueNDRangeKernel(commandQueue, kernel, 2, NULL, global_work_size, NULL, 0, NULL, NULL);
    err |= clEnqueueReadBuffer(commandQueue, result_matrix_buffer, CL_TRUE, 0, matrix_size, result, 0, NULL, NULL);
    if (err != CL_SUCCESS) {
        printf("Error: Failed to execute kernel! %d\n", err);
        exit(1);
    }

    clReleaseMemObject(first_matrix_buffer);
    clReleaseMemObject(second_matrix_buffer);
    clReleaseMemObject(result_matrix_buffer);
    return result;
}