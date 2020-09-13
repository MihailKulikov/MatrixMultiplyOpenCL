#include <stdio.h>

char *multiplyMatrix(const char *, const char *, int);

char *getTransitiveClosure(char *adjacency_matrix, int node_count){
    if (node_count == 0 || node_count == 1)
        return adjacency_matrix;

    for (int i = 0; i < node_count; i++){
        adjacency_matrix[i * node_count + i] = 1;
    }

    char *res = NULL;
    int power = node_count - 1;
    while (power)
        if (power & 1){
            if (res == NULL)
                res = adjacency_matrix;
            else
                res = multiplyMatrix(res, adjacency_matrix, node_count);
            --power;
        }else{
            adjacency_matrix = multiplyMatrix(adjacency_matrix, adjacency_matrix, node_count);
            power >>= 1;
        }

    return res;
}