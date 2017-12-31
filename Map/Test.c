#include "Map.h" 
#include <stdio.h>

/**
 * A lot of this can be reused across test modules. This may get
 * refactored if there is time.
 */

typedef struct Test
{
	int (*test)();
	const char* name;
} Test;

const char* reportString(int val)
{
	if(val)
	{
		return "Pass";
	}
	return "Fail";
}

int testCreateMap()
{
	int i, j, retVal = 1;

	// Construct a game map
    Map* m = createMap(3);

    // Test if size is created successfully.
    if (m->size != 3) retVal &= 0;

    // Test that board initialization worked
    for (i = 0; i < 3 && retVal; ++i)
    {
    	for (j = 0; j < 3 && retVal; ++j)
    	{
    		if (m->board[i][j] != NONE)
    		{
    			retVal &= 0;
    		}
    	}
    }

    // We're finished, clear the memory.
    deleteMap(m);

    // Return the pass/fail
    return retVal;
}

int main()
{
	int i, success = 1;

	Test tests[1];
	tests[0].test = &testCreateMap;
	tests[0].name = "testCreateMap";

	for (i = 0; i < (sizeof(tests)/sizeof(tests[0])); ++i)
	{
		success &= tests[i].test();
		printf("Running %s: %s\n", tests[i].name, reportString(success));

		if (!success)
		{
			break;
		}
	}
	return success;
}
