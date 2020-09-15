#include <CL/cl.h>
#include <stdio.h>

cl_context context;
cl_kernel kernel;
cl_command_queue commandQueue;

void initializeOpenCL();
char *getTransitiveClosure(char *, const char *, int);
void runAllTests();

int main(int argc, char *argv[]) {
    initializeOpenCL();
    for (int i = 1; i < argc; i++){
	if (argv[i][0] == '-' && argv[i][1] == 't'){
		runAllTests();
		return 0;
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

    char *result = (char *)malloc(vCount * vCount);
    getTransitiveClosure(result, adjacencyMatrix, vCount);

    for (int i = 0; i < vCount; i++) {
        for (int j = 0; j < vCount; j++) {
            printf("%i%s", result[i * vCount + j], (j < vCount - 1) ? " " : "\n");
        }
    }

    free(result);
    free(adjacencyMatrix);
    clReleaseContext(context);
    clReleaseKernel(kernel);
    clReleaseCommandQueue(commandQueue);
    return 0;
}