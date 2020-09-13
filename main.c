#include <CL/cl.h>
#include <stdio.h>

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

void initializeOpenCL();
char *multiplyMatrix(const char *first_matrix, const char *second_matrix, int matrix_order);

int main() {
    initializeOpenCL();

    printf("Enter the number of vertices of the graph\n");
    int vCount = 0;
    scanf("%i", &vCount);

    printf("Enter incidence table of the graph\n");
    char *incidenceTable = (char *)malloc(vCount * vCount);
    for (int i = 0; i < vCount * vCount; i++){
        scanf("%i", &incidenceTable[i]);
    }

    for (int i = 0; i < vCount; i++){
        for (int j = 0; j < vCount; j++){
            printf("%i%s", incidenceTable[i * vCount + j], (j < vCount - 1) ? " " : "\n");
        }
    }

    free(incidenceTable);
    clReleaseContext(context);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    return 0;
}