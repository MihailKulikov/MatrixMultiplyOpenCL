#include "../TestFramework/CuTest.h"

char *multiplyMatrix(const char *, const char *, int);

void FirstTestMatrixMultiply(CuTest *tc){
    const char first_matrix[] = {0, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0};
    const char second_matrix[] = {1, 1, 1,
                                  1, 1, 1,
                                  1, 1, 1};
    const char expected[] = {0, 0, 0,
                             0, 0, 0,
                             0, 0, 0};

    char *actual = multiplyMatrix(first_matrix, second_matrix, 3);

    for (int i = 0; i < 9; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void SecondTestMatrixMultiply(CuTest *tc){

}