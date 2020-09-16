#include <malloc.h>
#include <string.h>

void *multiplyMatrix(char *, const char *, const char *, int);

void *getTransitiveClosure(char *result, const char *adjacency_matrix, int node_count) {
    if (node_count == 0)
        return result;

    if (node_count == 1) {
        result[0] = 1;
        return result;
    }

    char *local_adjacency_matrix = (char *) malloc(node_count * node_count * sizeof(char));
    memcpy(local_adjacency_matrix, adjacency_matrix, node_count * node_count);

    for (int i = 0; i < node_count; i++) {
        local_adjacency_matrix[i * node_count + i] = 1;
    }

    char flag = 0;
    int power = node_count - 1;
    while (power)
        if (power & 1) {
            if (flag == 0) {
                flag++;
                memcpy(result, local_adjacency_matrix, node_count * node_count);
            } else {
                multiplyMatrix(result, result, local_adjacency_matrix, node_count);
            }
            --power;
        } else {
            multiplyMatrix(local_adjacency_matrix, local_adjacency_matrix, local_adjacency_matrix, node_count);
            power >>= 1;
        }

    free(local_adjacency_matrix);
    return result;
}