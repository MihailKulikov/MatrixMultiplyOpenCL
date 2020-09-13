#include <CL/cl.h>
#include <stdio.h>
#include <unistd.h>

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

void initializeOpenCL();
char *multiplyMatrix(const char *first_matrix, const char *second_matrix, int matrix_order);
void runAllTests();

int main(int argc, char *argv[]) {
    initializeOpenCL();
    int opt;
    while ((opt = getopt(argc, argv, "t")) != -1) {
        switch (opt) {
            case 't': {
                runAllTests();

                return 0;
            }
        }
    }

    printf("Enter the number of vertices of the graph\n");
    int vCount = 0;
    scanf("%i", &vCount);

    printf("Enter incidence table of the graph\n");
    char *adjacencyMatrix = (char *) malloc(vCount * vCount);
    for (int i = 0; i < vCount * vCount; i++) {
        scanf("%i", &adjacencyMatrix[i]);
    }

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            printf("%i%s", adjacencyMatrix[i * vCount + j], (j < vCount - 1) ? " " : "\n");
        }
    }

    free(adjacencyMatrix);
    clReleaseContext(context);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    return 0;
}