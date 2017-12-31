#include "Map.h" 
#include "../Test/Test.h"
#include <stdlib.h>

#define NUM_TESTS 4

Result testCreateMap()
{
	// Variables
	int i, j;
	Result retVal = PASS;

	// Construct a game map
    Map* m = createMap(3);

    // Test if size is created successfully.
    if (m->size != 3) retVal = FAIL;

    // Test that board initialization worked
    for (i = 0; i < 3 && retVal != FAIL; ++i)
    {
    	for (j = 0; j < 3 && retVal != FAIL; ++j)
    	{
    		// The board should be empty.
    		if (m->board[i][j] != NONE)
    		{
    			retVal = FAIL;
    		}
    	}
    }

    // We're finished, clear the memory.
    deleteMap(m);

    // Return the pass/fail
    return retVal;
}

Result testStateToString()
{
	return PASS;
}

Result testSetMapState()
{
	// Variables
	int i, j;

	// Construct a game map
    Map* m = createMap(3);

    // Test invalid coordinates and invalid state
    if (setMapState(m, 7, 7, X)) return FAIL;
    if (setMapState(m, 1, 1, TIE)) return FAIL;

    // Test setting values to x
    for (i = 0; i < 3; ++i)
    {
    	for (j = 0; j < 3; ++j)
    	{
    		if (!setMapState(m, i, j, X)) return FAIL;
    	}
    }
    return PASS;
}

Result testDetermineMapWinner()
{
	return PASS;
}

int main()
{
	// Setup a place for the test suit
	TestSuit suit;

	// Load variables for the test suit.
	suit.size = NUM_TESTS;

	// Ask for memory for the test suit.
	suit.tests = (Test *) malloc(sizeof(Test) * NUM_TESTS);

	// If the memory allocation fails the test fails
	if (!suit.tests)
	{
		return -1;
	}

	// Set the suit name.
	suit.name = "Map Tests";

	// Load the test suit with actual tests.
	suit.tests[0].test = &testCreateMap;
	suit.tests[0].name = "testCreateMap";
	suit.tests[1].test = &testStateToString;
	suit.tests[1].name = "testStateToString";
	suit.tests[2].test = &testSetMapState;
	suit.tests[2].name = "testSetMapState";
	suit.tests[3].test = &testDetermineMapWinner;
	suit.tests[3].name = "testDetermineMapWinner";


	return (int) runTestSuit(&suit);
}
