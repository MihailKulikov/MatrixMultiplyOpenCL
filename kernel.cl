__kernel void
matrixMult(__global char *result_matrix,
    __global char *first_matrix,
    __global char *second_matrix,
    int matrix_order)
{
    int current_row = get_global_id(0);
    int current_column = get_global_id(1);
    char value = 0;
    for (int i = 0; i < matrix_order; ++i)
    {
        char elementA = first_matrix[current_row * matrix_order + i];
        char elementB = second_matrix[i * matrix_order + current_column];
        value = elementA & elementB;
        if (value)
            break;
    }
    result_matrix[current_row * matrix_order + current_column] = value;
}