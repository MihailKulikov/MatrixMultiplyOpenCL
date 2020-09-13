#include "../TestFramework/CuTest.h"

char *getTransitiveClosure(char *, int);

void testSizeZeroGetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[0];
    int node_count = 0;

    char *result = getTransitiveClosure(adjacency_matrix, node_count);

    CuAssertPtrEquals(tc, adjacency_matrix, result);
}

void testSizeOneGetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[1] = {1};
    int node_count = 1;

    char *result = getTransitiveClosure(adjacency_matrix, node_count);

    CuAssertPtrEquals(tc, adjacency_matrix, result);
}

void testSizeFiveGetTransitiveClosure(CuTest *tc){
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

    char *actual = getTransitiveClosure(adjacency_matrix, 5);

    for (int i = 0; i < 25; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

void testSizeFourGetTransitiveClosure(CuTest *tc){
    char adjacency_matrix[16] = {0, 0, 1, 0,
                                 1, 0, 0, 1,
                                 0, 0, 0, 0,
                                 0, 1, 0, 0};
    char expected[16] = {0, 0, 1, 0,
                         1, 1, 1, 1,
                         0, 0, 0, 0,
                         1, 1, 1, 1};

    char *actual = getTransitiveClosure(adjacency_matrix, 4);

    for (int i = 0; i < 16; i++){
        CuAssertIntEquals(tc, expected[i], actual[i]);
    }
}

CuSuite *transitiveClosureGetSuite(){
    CuSuite *suite = CuSuiteNew();
    SUITE_ADD_TEST(suite, testSizeOneGetTransitiveClosure);
    SUITE_ADD_TEST(suite, testSizeZeroGetTransitiveClosure);
    SUITE_ADD_TEST(suite, testSizeFiveGetTransitiveClosure);
    SUITE_ADD_TEST(suite, testSizeFourGetTransitiveClosure);

    return suite;
}

