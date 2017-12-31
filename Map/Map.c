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
			for (i = 0; i < size; ++i)
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

				// Loop back over the new row and set all the new entries to NONE
				for (j = 0; j < size; ++j)
				{
					retVal->board[i][j] = NONE;
				}
			}

			// Store the size into the struct for dimension tracking.
			retVal->size = size;
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

void deleteMap(Map* map)
{
	// Variables
	int i;

	// Loop through the board and delete the rows.
	for (i = 0; i < map->size; ++i)
	{
		free(map->board[i]);
	}

	// Free the board pointer
	free(map->board);

	// Finally, free the map
	free(map);
}

const char* stateToString(TileState state)
{
	/**
	 * TODO
	 * Translate the given state to a string
	 * the values should map as follows:
	 * X    = X
	 * Y    = Y
	 * NONE = _
	 * TIE  = Tie
	 */
	return "";
}

int setMapState(Map* map, int xVal, int yVal, TileState state)
{
	/**
	 * TODO
	 * Set the state of a given map position to the provided values.
	 * If xVal and yVal are in valid ranges and the state is valid, then
	 * the position on the game map should be set to the tile.
	 *
	 * The return value is a completion code. The codes follow:
	 *  1 = Success
	 *  0 = Invalid Coordinates
	 * -1 = Invalid state
	 */
	return 0;
}

TileState determineMapWinner(Map* map)
{
	/**
	 * TODO
	 * Loop over the map and determine a winner. This is either X, Y, NONE, or TIE.
	 */
	return NONE;
}
