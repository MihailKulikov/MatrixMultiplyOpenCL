#include <stdio.h>
#include <CL/cl.h>

long loadCLKernel(const char* path, char **buf) {
    FILE *file_pointer;
    size_t file_size;
    long off_end;
    int ret;

    file_pointer = fopen(path, "r");
    if (NULL == file_pointer) {
        return -1L;
    }

    ret = fseek(file_pointer, 0L, SEEK_END);
    if (0 != ret) {
        return -1L;
    }

    if (0 > (off_end = ftell(file_pointer))) {
        return -1L;
    }
    file_size = (size_t) off_end;

    *buf = (char *) malloc(file_size + 1);
    if (NULL == *buf) {
        return -1L;
    }

    rewind(file_pointer);

    size_t read_elements_count = fread(*buf, sizeof(char), file_size, file_pointer);

    if (EOF == fclose(file_pointer)) {
        free(*buf);
        return -1L;
    }

    (*buf)[read_elements_count] = '\0';

    return (long) read_elements_count;
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
    cl_context context = clCreateContextFromType(properties, CL_DEVICE_TYPE_GPU, NULL, NULL, &error);
    if (error != CL_SUCCESS){
        printf("Fail clCreateContextFromType");
        return EXIT_FAILURE;
    }

    cl_command_queue commandQueue = clCreateCommandQueue(context, deviceIDs[0], 0, &error);
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
    if (error != CL_SUCCESS){
        printf("Fail clCreateProgramWithSource");
        return EXIT_FAILURE;
    }
    if (clBuildProgram(program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS){
        printf("Fail");
    }

    cl_kernel kernel = clCreateKernel(program, "matrixMult", &error);
    if (error != CL_SUCCESS){
        printf("Fail");
    }
    return 0;
}
