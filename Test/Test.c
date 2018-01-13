#include "Test.h"
#include <stdio.h>

const char* reportString(Result result)
{
    // Check to see if the result is a pass.
    if(result == PASS)
    {
        // Return a string for pass.
        return "Pass";
    }
    // It must have been fail. Return a string for fail.
    return "Fail";
}

Result runTestSuite(TestSuite* suite)
{
    // Variables
    int i;
    Result retVal;

    // Print the test suit name.
    printf("Running test suit: %s\n", suite->name);

    // Loop through the test suite and run each test
    for (i = 0, retVal = PASS; i < suite->size && retVal == PASS; ++i)
    {
        // Run the test and print the result.
        Result tmp = suite->tests[i].test();
        printf("\t%s: %s\n", suite->tests[i].name, reportString(tmp));
    }

    // Return the result.
    return retVal;
}
