#include "func.h"

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

int main() {
    initializeOpenCL();
    char A[4] = {0, 0, 0, 0};
    char B[4] = {1, 1, 1, 1};
    char matrix_order = 2;
    char *result = multiplyMatrix(A, B, matrix_order);
    for (int i = 0; i < 4; i++) {
        printf("%i ", result[i]);
    }
    return 0;
}