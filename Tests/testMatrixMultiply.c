#include "../TestFramework/CuTest.h"

void *multiplyMatrix(char *, const char *, const char *, int);

void testSizeThreeMatrixMultiply(CuTest *tc){
    const char first_matrix[] = {0, 1, 0,
                                 1, 0, 1,
                                 0, 1, 1};
    const char second_matrix[] = {1, 1, 0,
                                  0, 0, 0,
                                  0, 1, 1};
    const char expected[] = {0, 0, 0,
                             1, 1, 1,
                             0, 1, 1};
    char actual[9];

    CuAssertPtrNotNull(tc, multiplyMatrix(actual, first_matrix, second_matrix, 3));

    for (int i = 0; i < 9; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testSizeTwoMatrixMultiply(CuTest *tc){
    const char first_matrix[] = {0, 1,
                                 1, 0};
    const char second_matrix[] = {1, 0,
                                  0, 1};
    const char expected[] = {0, 1,
                             1, 0};
    char actual[4];

    CuAssertPtrNotNull(tc, multiplyMatrix(actual, first_matrix, second_matrix, 2));
    for (int i = 0; i < 4; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testSizeFourMatrixMultiply(CuTest *tc){
    const char first_matrix[] = {0, 1, 0, 1,
                                 1, 1, 0, 0,
                                 0, 0, 0, 1,
                                 1, 0, 0, 0};
    const char second_matrix[] = {1, 0, 1, 0,
                                  0, 0, 1, 1,
                                  1, 1, 1, 0,
                                  0, 1, 1 ,1};
    const char expected[] = {0, 1, 1, 1,
                             1, 0, 1, 1,
                             0, 1, 1, 1,
                             1, 0, 1, 0};
    char actual[16];

    CuAssertPtrNotNull(tc, multiplyMatrix(actual, first_matrix, second_matrix, 4));
    for (int i = 0; i < 16; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testZeroMatricesMatrixMultiply(CuTest *tc){
    const char first_matrix[] = {0, 0, 0, 0,
                                 0, 0, 0, 0,
                                 0, 0, 0, 0,
                                 0, 0, 0, 0};
    const char second_matrix[] = {0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0, 0,
                                  0, 0, 0 ,0};
    const char expected[] = {0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0,
                             0, 0, 0, 0};
    char actual[16];

    CuAssertPtrNotNull(tc, multiplyMatrix(actual, first_matrix, second_matrix, 4));
    for (int i = 0; i < 16; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

CuSuite *multiplyMatrixGetSuite(){
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSizeThreeMatrixMultiply);
    SUITE_ADD_TEST(suite, testSizeTwoMatrixMultiply);
    SUITE_ADD_TEST(suite, testSizeFourMatrixMultiply);
    SUITE_ADD_TEST(suite, testZeroMatricesMatrixMultiply);

    return suite;
}