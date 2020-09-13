#include "../TestFramework/CuTest.h"
#include <stdio.h>

CuSuite *multiplyMatrixGetSuite();
CuSuite *transitiveClosureGetSuite();

void runAllTests() {
    CuString *output = CuStringNew();
    CuSuite *suite = CuSuiteNew();

    CuSuiteAddSuite(suite, multiplyMatrixGetSuite());
    CuSuiteAddSuite(suite, transitiveClosureGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}