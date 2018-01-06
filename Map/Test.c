#include "Map.h" 
#include "../Test/Test.h"

#include <stdlib.h>
#include <string.h>

#define NUM_TESTS 5

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

    // We're finished, clear the memory.correctly
    deleteMap(m);

    // Return the pass/fail
    return retVal;
}

Result testStateToString()
{
    // Test to see if the strings are returned
    if (strcmp("X", stateToString(X)) != 0) return FAIL;
    if (strcmp("Y", stateToString(Y)) != 0) return FAIL;
    if (strcmp("None", stateToString(NONE)) != 0) return FAIL;
    if (strcmp("Tie", stateToString(TIE)) != 0) return FAIL;
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
    if (setMapState(m, 1, 1, NONE)) return FAIL;

    // Test setting values to x
    for (i = 0; i < 3; ++i)
    {
    	for (j = 0; j < 3; ++j)
    	{
    		// Test if the state is set properly
    		if (!setMapState(m, i, j, X)) return FAIL;
    		if (m->board[i][j] != X) return FAIL;
    	}
    }

    // Make sure that you can reset a set state.
    if (setMapState(m, 1, 2, X)) return FAIL;

    // Reset the map for more tests
    deleteMap(m);
    m = createMap(5);

    // Test setting values to y
    for (i = 0; i < 5; ++i)
    {
    	for (j = 0; j < 5; ++j)
    	{
    		// Test if the state is set properly
    		if (!setMapState(m, i, j, Y)) return FAIL;
    		if (m->board[i][j] != Y) return FAIL;
    	}
    }

    // Cleanup
    deleteMap(m);

    // If we have made it this far, nothing bad happened.
    return PASS;
}

Result testDetermineMapWinner()
{
	// Create a map and fill row 1
    Map* m = createMap(3);
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[0][0] = X;
    m->board[1][0] = X;
    m->board[2][0] = X;
    if (!determineMapWinner(m) == X) return FAIL;
    deleteMap(m);

    // Create a map and fill row 2
    m = createMap(3);
    m->board[0][1] = Y;
    m->board[1][1] = Y;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[2][1] = Y;
    if (!determineMapWinner(m) == Y) return FAIL;
    deleteMap(m);

    // Create a map and fill row 3
    m = createMap(3);
    m->board[0][2] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[1][2] = X;
    m->board[2][2] = X;
    if (!determineMapWinner(m) == X) return FAIL;
    deleteMap(m);

    // Create a map and fill column 1
    m = createMap(3);
    m->board[0][0] = Y;
    m->board[0][1] = Y;
    m->board[0][2] = Y;
    if (!determineMapWinner(m) == Y) return FAIL;
    deleteMap(m);

    // Create a map and fill column 2
    m = createMap(3);
    m->board[1][0] = Y;
    m->board[1][1] = Y;
    m->board[1][2] = Y;
    if (!determineMapWinner(m) == Y) return FAIL;
    deleteMap(m);

    // Create a map and fill column 3
    m = createMap(3);
    m->board[2][0] = X;
    m->board[2][1] = X;
    m->board[2][2] = X;
    if (!determineMapWinner(m) == X) return FAIL;
    deleteMap(m);

    // Create a map and fill diagonal 1
    m = createMap(3);
    m->board[0][0] = X;
    m->board[1][1] = X;
    m->board[2][2] = X;
    if (!determineMapWinner(m) == X) return FAIL;
    deleteMap(m);

    // Create a map and fill diagonal 2
    m = createMap(3);
    m->board[2][0] = Y;
    m->board[1][1] = Y;
    m->board[0][2] = Y;
    if (!determineMapWinner(m) == Y) return FAIL;
    deleteMap(m);

    // Create tied map
    m = createMap(3);
    m->board[0][0] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[0][1] = Y;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[0][2] = Y;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[1][0] = Y;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[1][1] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[1][2] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[2][0] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[2][1] = Y;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[2][2] = Y;
    if (!determineMapWinner(m) == TIE) return FAIL;
    deleteMap(m);

    // Create a large map and fill diagonal 1
    m = createMap(6);
    m->board[0][0] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[1][1] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[2][2] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[3][3] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[4][4] = X;
    if (!determineMapWinner(m) == NONE) return FAIL;
    m->board[5][5] = X;
    if (!determineMapWinner(m) == X) return FAIL;
    deleteMap(m);

    // If we made it this far, its a success!
    return PASS;
}

Result testGetEmptyTiles()
{
    /**
     * TODO
     * Test the generation and population of tile nodes.
     * Remember that this is a linked list and and memory
     * should be freed between different test situations to
     * prevent memory leaks.
     */
    return FAIL;
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
    suit.tests[4].test = &testGetEmptyTiles;
    suit.tests[4].name = "testGetEmptyTiles";

    // Run the test suite
    return (int) runTestSuite(&suit);
}
