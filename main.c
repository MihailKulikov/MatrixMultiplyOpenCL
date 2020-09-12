#include "func.h"

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

int main() {
    initializeOpenCL();
    char A[4] = {0, 1, 0, 0};
    char B[4] = {1, 1, 1, 1};
    char matrix_order = 2;
    char *result = multiplyMatrix(A, B, matrix_order);
    for (int i = 0; i < 4; i++) {
        printf("%i ", result[i]);
    }

    int test_order = 10000;
    char *C = malloc(test_order * test_order);
    char *D = malloc(test_order * test_order);
    for (int i = 0; i < test_order * test_order; i++){
        C[i] = 0;
        D[i] = 0;
    }
    result = multiplyMatrix(C, D, test_order);
    for (int i = 0; i < 250000; ++i){
        printf("%i ", result[i]);
    }
    free(C);
    free(D);
    clReleaseContext(context);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    return 0;
}