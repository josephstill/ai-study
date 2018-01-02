/**
 * This enum defines the unit test result.
 */
typedef enum Result
{
    FAIL = -1,
    PASS = 0
} Result;

/**
 * This struct defines a container for a unit test.
 *
 * @param test: The callback function for the test.
 * @param name: The name of the test.
 */
typedef struct Test
{
    Result (*test)();
    const char* name;
} Test;

/**
 * This struct defines a test suit of unit tests.
 *
 * @param tests: A list of tests.
 * @param size: The number of tests.
 */
typedef struct TestSuit
{
    Test* tests;
    int size;
    const char* name;
} TestSuit;

/**
 * Converts a bool pass/fail value into a string.
 *
 * @param result: The pass/fail value
 * @return: A string representation of the result.
 */
const char* reportString(Result result);

/**
 * Runs a test suit.
 *
 * @param suit: The test suit to run.
 * @return: A pass/fail result.
 */
Result runTestSuite(TestSuit* suit);
