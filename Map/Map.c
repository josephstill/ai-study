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
	 * NONE = 'None'
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
    // Variables
    int i, j, x, y;
    int boardFull = 1;

    // Loop over the map and determine a winner.
    // check verticals
    for (i = 0; i < map->size; ++i)
    {
    	for (j = 0, x = 0, y = 0; j < map->size; ++j)
        {
            if (map->board[j][i] == X)
                x++;
            else if (map->board[j][i] == Y)
                y++;
            else
                boardFull = 0;

            if (x == map->size)
                return X;
            else if (y == map->size)
                return Y;
        }
    }

    // check horizontals
    for (i = 0; i < map->size; ++i)
    {
        for (j = 0, x = 0, y = 0; j < map->size; ++j)
        {
            if (map->board[i][j] == X)
                x++;
            else if (map->board[i][j] == Y)
                y++;

            if (x == map->size)
                return X;
            else if (y == map->size)
                return Y;
        }
    }

    // check diagonal (top-left to bottom-right)
    for (i = 0, x = 0, y = 0; i < map->size; ++i)
    {
        if (map->board[i][i] == X)
            x++;
        if (map->board[i][i] == Y)
            y++;

        if (x == map->size)
            return X;
        else if (y == map->size)
            return Y;
    }

    // check diagonal (top-right to bottom-left)
    for (i = map->size - 1, x = 0, y = 0; i >= 0; --i)
    {
        if (map->board[i][i] == X)
            x++;
        if (map->board[i][i] == Y)
            y++;

        if (x == map->size)
            return X;
        else if (y == map->size)
            return Y;
    }

    if (boardFull)
        return TIE;
    else
	   return NONE;
}

TileListNode* getEmptyTiles(Map* map)
{
	// Variables
    int i, j;
    TileListNode *toDelete, *tmp, *retVal = NULL;
    TileListNode **currentNode;

    // Loop through the board an search for empty nodes.
	for (i = 0, currentNode = &retVal; i < map->size; ++i)
	{
        for (j = 0; j < map->size; ++j)
        {
            if (map->board[i][j] == NONE)
            {
                // Create a node to store the information in.
                *currentNode = (TileListNode*) malloc(sizeof(TileListNode));

                // Check to see if creation worked
                if (!(*currentNode))
                {
                        // Loop through the list from start untill end and delete the node.
                    	for (toDelete = retVal; toDelete != NULL;)
                    	{
                            tmp = toDelete->next;
                            free(toDelete);
                            toDelete = tmp;
                    	}
                }

                // Fill out the map data
                (*currentNode)->x = i;
                (*currentNode)->y = j;
                (*currentNode)->next = NULL;

                // Advance the current node pointer to the new current node
                currentNode = &(*currentNode)->next;
            }
        }
    }

    // Return the result.
    return retVal;
}

int mapEquivalent(Map* a, Map* b)
{
    /**
     * TODO
     * Check if the two maps have the exact same entries.
     */
    return 0;
}

const char* mapToString(Map m)
{
    /**
     * TODO
     * Generate a string representation of the map. I should look like this
     * -------
     * |X|Y| |
     * -------
     * | |X|Y|
     * -------
     * |Y|X| |
     * -------
     * The X and Y tokens are generated in another function. Be careful, there
     * may be a difference in what the function returns and how the map should look.
     */
    return "";
}
