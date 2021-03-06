#include "Map.h"
#include "../Test/Test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hoorqy! Preprocessor Directives! These constants and macros will help with tests
#define NUM_TESTS 9

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

    // Make sure that you can't reset a set state.
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
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[0][0] = X;
    m->board[1][0] = X;
    m->board[2][0] = X;
    if (determineMapWinner(m) != X) return FAIL;
    deleteMap(m);

    // Create a map and fill row 2
    m = createMap(3);
    m->board[0][1] = Y;
    m->board[1][1] = Y;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[2][1] = Y;
    if (determineMapWinner(m) != Y) return FAIL;
    deleteMap(m);

    // Create a map and fill row 3
    m = createMap(3);
    m->board[0][2] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[1][2] = X;
    m->board[2][2] = X;
    if (determineMapWinner(m) != X) return FAIL;
    deleteMap(m);

    // Create a map and fill column 1
    m = createMap(3);
    m->board[0][0] = Y;
    m->board[0][1] = Y;
    m->board[0][2] = Y;
    if (determineMapWinner(m) != Y) return FAIL;
    deleteMap(m);

    // Create a map and fill column 2
    m = createMap(3);
    m->board[1][0] = Y;
    m->board[1][1] = Y;
    m->board[1][2] = Y;
    if (determineMapWinner(m) != Y) return FAIL;
    deleteMap(m);

    // Create a map and fill column 3
    m = createMap(3);
    m->board[2][0] = X;
    m->board[2][1] = X;
    m->board[2][2] = X;
    if (determineMapWinner(m) != X) return FAIL;
    deleteMap(m);

    // Create a map and fill diagonal 1
    m = createMap(3);
    m->board[0][0] = X;
    m->board[1][1] = X;
    m->board[2][2] = X;
    if (determineMapWinner(m) != X) return FAIL;
    deleteMap(m);

    // Create a map and fill diagonal 2
    m = createMap(3);
    m->board[2][0] = Y;
    m->board[1][1] = Y;
    m->board[0][2] = Y;
    if (determineMapWinner(m) != Y) return FAIL;
    deleteMap(m);

    // Create tied map
    m = createMap(3);
    m->board[0][0] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[0][1] = Y;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[0][2] = Y;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[1][0] = Y;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[1][1] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[1][2] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[2][0] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[2][1] = Y;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[2][2] = Y;
    if (determineMapWinner(m) != TIE) return FAIL;
    deleteMap(m);

    // Create a large map and fill diagonal 1
    m = createMap(6);
    m->board[0][0] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[1][1] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[2][2] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[3][3] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[4][4] = X;
    if (determineMapWinner(m) != NONE) return FAIL;
    m->board[5][5] = X;
    if (determineMapWinner(m) != X) return FAIL;
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

     // Variables
     TileListNode* head = NULL;
     TileListNode* temp = NULL;
     int i, j, size;

     // Create map and test empty
     Map* m = createMap(3);
     if (!getEmptyTiles(m, &size)) return FAIL;
     if (size != 9) return FAIL;

     head = getEmptyTiles(m, &size);

     // Check the x,y map data matches
     for (i = 0; i < 3; ++i)
     {
         for (j = 0; j < 3; ++j)
         {
             if (head->x != i) return FAIL;
             if (head->y != j) return FAIL;
             temp = head;
             head = head->next;
             free(temp);
         }
     }
     free(head);

     // Fill and test full map
     m->board[0][0] = Y;
     m->board[0][1] = X;
     m->board[0][2] = X;
     m->board[1][0] = X;
     m->board[1][1] = Y;
     m->board[1][2] = Y;
     m->board[2][0] = Y;
     m->board[2][1] = X;
     m->board[2][2] = X;
     if (getEmptyTiles(m, &size)) return FAIL;

     // Clean up
     deleteMap(m);

    return PASS;
}

Result testMapEquivalent()
{
    // Variables
    int i, j;
    Map *a, *b;

    // Make some test maps.
    a = createMap(3);
    b = createMap(3);

    // Empty maps are equal.
	if (!mapEquivalent(a, b)) return FAIL;

    // Not so equal
    a->board[0][0] = X;
    if (mapEquivalent(a, b)) return FAIL;

    b->board[0][0] = X;
    if (!mapEquivalent(a, b)) return FAIL;

    b->board[1][1] = X;
    b->board[2][2] = X;
    if (mapEquivalent(a, b)) return FAIL;

    a->board[1][1] = X;
    a->board[2][2] = X;
    if (!mapEquivalent(a, b)) return FAIL;

    // Completely different
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
           a->board[i][j] = X;
           b->board[i][j] = Y;
        }
    }
    if (mapEquivalent(a, b)) return FAIL;

    // Now the same.
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
           a->board[i][j] = Y;
        }
    }
    if (!mapEquivalent(a, b)) return FAIL;

    // Clean up a bit
    deleteMap(a);
    deleteMap(b);

    // Test that maps of different sizes shouldn't be equivalent.
    a = createMap(3);
    b = createMap(5);

    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
           a->board[i][j] = X;
           b->board[i][j] = X;
        }
    }
    if (mapEquivalent(a, b)) return FAIL;

    // Clean up the rest.
    deleteMap(a);
    deleteMap(b);

    return PASS;
}

Result testMapToString()
{
    // Variables
    int i, j;
    const char* tests[] =
    {
        "-------\n| | | |\n-------\n| | | |\n-------\n| | | |\n-------",
        "-------\n|%s| | |\n-------\n| |%s| |\n-------\n| | |%s|\n-------",
        "-------\n|%s| |%s|\n-------\n| |%s|%s|\n-------\n|%s| |%s|\n-------",
        "-------\n|%s|%s|%s|\n-------\n|%s|%s|%s|\n-------\n|%s|%s|%s|\n-------",
        "-----------\n| | | | | |\n-----------\n| | | | | |\n-----------\n| | | | | |\n-----------\n| | | | | |\n-----------\n| | | | | |\n-----------"
    };
    char testBuffer[256];
    Map *m;

    // Setup the map
    m = createMap(3);

    // Test an empty map
    if (strcmp(tests[0], mapToString(m)) != 0) return FAIL;

    // Test for string one
    m->board[0][0] = X;
    m->board[1][1] = X;
    m->board[2][2] = X;
    sprintf(testBuffer, tests[1], stateToString(X), stateToString(X), stateToString(X));
    if (strcmp(testBuffer, mapToString(m)) != 0) return FAIL;

    // Test for string two
    m->board[0][2] = Y;
    m->board[1][2] = Y;
    m->board[2][0] = Y;
    sprintf(testBuffer,
            tests[2],
            stateToString(X),
            stateToString(Y),
            stateToString(X),
            stateToString(Y),
            stateToString(Y),
            stateToString(X));
    if (strcmp(testBuffer, mapToString(m)) != 0) return FAIL;

    // Test for string three
    m->board[0][1] = Y;
    m->board[1][0] = Y;
    m->board[2][1] = Y;
    sprintf(testBuffer,
            tests[3],
            stateToString(X),
            stateToString(Y),
            stateToString(Y),
            stateToString(Y),
            stateToString(X),
            stateToString(Y),
            stateToString(Y),
            stateToString(Y),
            stateToString(X));
    if (strcmp(testBuffer, mapToString(m)) != 0) return FAIL;

    // For fun, we'll test something that shouldn't happen.
    for (i = 0; i < 3; ++i)
    {
        for (j = 0; j < 3; ++j)
        {
            m->board[i][j] = TIE;
        }
    }
    if (strcmp(tests[0], mapToString(m)) != 0) return FAIL;

    // Cleanup
    deleteMap(m);
    m = createMap(5);

    if (strcmp(tests[4], mapToString(m)) != 0) return FAIL;
    deleteMap(m);

    return PASS;
}

Result testDeepCopy()
{
    // Variables
    int i, j;
    Map *m, *n;

    // Set up the test
    m = createMap(3);
    n = deepCopy(m);

    // Make sure the copy did stuff
    if (!n) return FAIL;

    // Make sure the copy doesn't just return the same pointer
    if (n == m) return FAIL;

    // Make sure the sizes match
    if (m->size != n->size) return FAIL;

    // Make sure all the items in the map match
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] != n->board[i][j]) return FAIL;
        }
    }

    // Prepare for the next test.
    deleteMap(n);

    // Setup a test.
    m->board[0][0] = Y;
    m->board[0][1] = X;
    m->board[1][2] = Y;
    m->board[2][2] = X;

    // Perform the next test
    n = deepCopy(m);

    // Make sure the copy did stuff
    if (!n) return FAIL;

    // Make sure the copy doesn't just return the same pointer
    if (n == m) return FAIL;

    // Make sure the sizes match
    if (m->size != n->size) return FAIL;

    // Make sure all the items in the map match
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] != n->board[i][j]) return FAIL;
        }
    }

    // Prepare for the next test.
    deleteMap(n);

    // Setup a test.
    m->board[0][2] = X;
    m->board[1][1] = Y;
    m->board[2][0] = Y;
    m->board[2][1] = X;
    m->board[2][2] = Y;

    // Perform the next test
    n = deepCopy(m);

    // Make sure the copy did stuff
    if (!n) return FAIL;

    // Make sure the copy doesn't just return the same pointer
    if (n == m) return FAIL;

    // Make sure the sizes match
    if (m->size != n->size) return FAIL;

    // Make sure all the items in the map match
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] != n->board[i][j]) return FAIL;
        }
    }

    // Now test that pointers are not copied for the board.
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            m->board[i][j] = X;
            n->board[i][j] = Y;
        }
    }

    // Make sure none of the elements match.
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] == n->board[i][j]) return FAIL;
        }
    }

    // Prepare for the next test.
    deleteMap(m);
    deleteMap(n);

    // The final test.
    m = createMap(5);

    // Load the new map.
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            m->board[i][j] = X;
        }
    }

    // Perform the final test
    n = deepCopy(m);

    // Make sure the copy did stuff
    if (!n) return FAIL;

    // Make sure the copy doesn't just return the same pointer
    if (n == m) return FAIL;

    // Make sure the sizes match
    if (m->size != n->size) return FAIL;

    // Make sure all the items in the map match
    for (i = 0; i < m->size; ++i)
    {
        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] != n->board[i][j]) return FAIL;
        }
    }

    // Prepare for the next test.
    deleteMap(m);
    deleteMap(n);

    return PASS;
}

Result testToggleTileState()
{
    // This should test all of the possible inputs.
    if (toggleTileState(X) != Y) return FAIL;
    if (toggleTileState(Y) != X) return FAIL;
    if (toggleTileState(NONE) != NONE) return FAIL;
    if (toggleTileState(TIE) != NONE) return FAIL;
    return PASS;
}

int main()
{
    // Setup a place for the test suite
    TestSuite suite;
    Result result;

    // Load variables for the test suite.
    suite.size = NUM_TESTS;

    // Ask for memory for the test suite.
    suite.tests = (Test *) malloc(sizeof(Test) * NUM_TESTS);

    // If the memory allocation fails the test fails
    if (!suite.tests)
    {
        return -1;
    }

    // Set the suit name.
    suite.name = "Map Tests";

    // Load the test suit with actual tests.
    suite.tests[0].test = &testCreateMap;
    suite.tests[0].name = "testCreateMap";
    suite.tests[1].test = &testStateToString;
    suite.tests[1].name = "testStateToString";
    suite.tests[2].test = &testSetMapState;
    suite.tests[2].name = "testSetMapState";
    suite.tests[3].test = &testDetermineMapWinner;
    suite.tests[3].name = "testDetermineMapWinner";
    suite.tests[4].test = &testGetEmptyTiles;
    suite.tests[4].name = "testGetEmptyTiles";
    suite.tests[5].test = &testMapEquivalent;
    suite.tests[5].name = "testMapEquivalent";
    suite.tests[6].test = &testMapToString;
    suite.tests[6].name = "testMapToString";
    suite.tests[7].test = &testDeepCopy;
    suite.tests[7].name = "testDeepCopy";
    suite.tests[8].test = &testToggleTileState;
    suite.tests[8].name = "testToggleTileState";

    // Run the test suite
    return (int) runTestSuiteNoFail(&suite);
}
