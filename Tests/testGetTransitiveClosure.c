#include "../TestFramework/CuTest.h"

void *getTransitiveClosure(char *, const char *, int);

void testId0GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[1] = {1};
    char result[1];

    CuAssertPtrNotNull(tc, getTransitiveClosure(result, adjacency_matrix, 1));
    CuAssertIntEquals(tc, 1, result[0]);
}

void testId1GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[25] = {0, 1, 0, 0, 0,
                                 0, 0, 1, 0, 0,
                                 0, 0, 0, 1, 1,
                                 0, 1, 0, 0, 0,
                                 0, 0, 0, 1, 0};
    char expected[25] = {1, 1, 1, 1, 1,
                         0, 1, 1, 1, 1,
                         0, 1, 1, 1, 1,
                         0, 1, 1, 1, 1,
                         0, 1, 1, 1, 1};
    char actual[25];

    CuAssertPtrNotNull(tc, getTransitiveClosure(actual, adjacency_matrix, 5));
    for (int i = 0; i < 25; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testId2GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[16] = {0, 0, 1, 0,
                                 1, 0, 0, 1,
                                 0, 0, 0, 0,
                                 0, 1, 0, 0};
    char expected[16] = {1, 0, 1, 0,
                         1, 1, 1, 1,
                         0, 0, 1, 0,
                         1, 1, 1, 1};
    char actual[16];

    CuAssertPtrNotNull(tc, getTransitiveClosure(actual, adjacency_matrix, 4));
    for (int i = 0; i < 16; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testId3GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[16] = {0, 1, 0, 0,
                               0, 0, 0, 1,
                               0, 0, 0, 0,
                               1, 0, 1, 0};
    char expected[16] = {1, 1, 1, 1,
                         1, 1, 1, 1,
                         0, 0, 1, 0,
                         1, 1, 1, 1};
    char actual[16];

    CuAssertPtrNotNull(tc, getTransitiveClosure(actual, adjacency_matrix, 4));
    for (int i = 0; i < 16; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testId4GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[9] = {0, 1, 0,
                                 0, 0, 1,
                                 1, 0, 0};
    char expected[9] = {1, 1, 1,
                         1, 1, 1,
                         1, 1, 1};
    char actual[9];

    CuAssertPtrNotNull(tc, getTransitiveClosure(actual, adjacency_matrix, 3));
    for (int i = 0; i < 9; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testId5GetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[9] = {1, 0, 0,
                                0, 1, 0,
                                0, 0, 1};
    char* expected = adjacency_matrix;
    char actual[9];

    CuAssertPtrNotNull(tc, getTransitiveClosure(actual, adjacency_matrix, 3));
    for (int i = 0; i < 9; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

CuSuite *transitiveClosureGetSuite(){
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testId0GetTransitiveClosure);
    SUITE_ADD_TEST(suite, testId1GetTransitiveClosure);
    SUITE_ADD_TEST(suite, testId2GetTransitiveClosure);
    SUITE_ADD_TEST(suite, testId3GetTransitiveClosure);
    SUITE_ADD_TEST(suite, testId4GetTransitiveClosure);
    SUITE_ADD_TEST(suite, testId5GetTransitiveClosure);

    return suite;
}

