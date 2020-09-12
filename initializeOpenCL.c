#include <CL/opencl.h>
#include <stdio.h>

extern cl_kernel kernel;
extern cl_context context;
extern cl_command_queue commandQueue;

long loadCLKernel(const char* , char **);

void initializeOpenCL() {
    cl_int error;
    cl_platform_id platformIds[2];
    error = clGetPlatformIDs(2, platformIds, NULL);
    if (error != CL_SUCCESS) {
        printf("Fail clGetPlatformIDs");
        exit(1);
    }

    cl_device_id deviceIDs[1];
    error = clGetDeviceIDs(platformIds[0], CL_DEVICE_TYPE_GPU, 1, deviceIDs, NULL);
    if (error != CL_SUCCESS) {
        printf("Fail clGetDeviceIDs");
        exit(1);
    }

    const cl_context_properties properties[] = {
            CL_CONTEXT_PLATFORM,
            (cl_context_properties) platformIds[0],
            0
    };
    context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &error);
    if (error != CL_SUCCESS) {
        printf("Fail clCreateContextFromType");
        exit(1);
    }

    commandQueue = clCreateCommandQueue(context, deviceIDs[0], 0, &error);
    if (error != CL_SUCCESS) {
        printf("Fail clCreateCommandQueue");
        exit(1);
    }

    char *kernelSource;
    long fileSize = loadCLKernel("kernel.cl", &kernelSource);
    if (fileSize < 0L) {
        perror("File read failed");
        exit(1);
    }

    cl_program program = clCreateProgramWithSource(context, 1, (const char **) &kernelSource, NULL, &error);
    free(kernelSource);
    if (error != CL_SUCCESS) {
        printf("Fail clCreateProgramWithSource");
        exit(1);
    }

    if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) {
        printf("Fail clBuildProgram");
        exit(1);
    }

    kernel = clCreateKernel(program, "matrixMult", &error);
    if (error != CL_SUCCESS) {
        printf("Fail clCreateKernel");
        exit(1);
    }

    clReleaseProgram(program);
}