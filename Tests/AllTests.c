#include "../TestFramework/CuTest.h"
#include <stdio.h>

CuSuite *multiplyMatrixGetSuite();

void runAllTests() {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, multiplyMatrixGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}