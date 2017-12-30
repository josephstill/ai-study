#include <stdlib.h>

#include "Map.h" 
 
Map* createMap(int size)
{
	// Variables
	int i, j;

	// Initialize memory for the map. This will create a map object only
	// It is still a requirement to create game board memory
	Map *retVal = (Map *) malloc(sizeof(Map));

	// Malloc might have failed, we'll check to prevent a segmentation fault.
	if (retVal)
	{
		// Next we'll initialize the game map. It is essentially a list of lists;
		// so, we'll initialize the list that holds the lists.
		retVal->board = (TileState **) malloc(sizeof(TileState *) * size);

		// Check if the initial list was created successfully
		if (retVal->board)
		{
			for(i = 0; i < size; ++i)
			{
				// Now we'll loop over the outer list and create inner lists to store the
				// actual game state.
				retVal->board[i] = (TileState *) malloc(sizeof(TileState) * size);

				// Check to see if the inner list was created correctly
				if (!retVal->board[i])
				{
					// There was an issue creating memory, free the memory that was created
					// then we will return null
					for (j = i - 1; j >= 0; --j)
					{
						free(retVal->board[j]);
					}

					// Free the memory for the game map
					free(retVal);

					// We shouldn't return a pointer to freed memory
					return NULL;
				}
			}
			//TODO the map is finished, we need to store the size in the map struct.
		}
		else
		{
			// Creation of the memory for the game board failed, free the memory for the map
			free(retVal);

			// We shouldn't return a pointer to freed memory
			return NULL;
		}
	}

	return retVal;
}
