#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    // A switch is easier than if else if else if...
    switch (state)
    {
        case X:
            return "X";
        case Y:
            return "Y";
        case TIE:
            return "Tie";
        case NONE: //Intentional Fall-through
        default:
            return "None";
    }
    // This should never happen; however, sometimes a compiler may not be happy without an explicit return
    return "None";
}

int setMapState(Map* map, int xVal, int yVal, TileState state)
{
    // Lets test the input for validity first.
    if (xVal >= map->size || xVal < 0) return 0;
    if (yVal >= map->size || yVal < 0) return 0;
    if (state != X && state != Y) return 0;
    if (map->board[xVal][yVal] != NONE) return 0;

    // Set the value
    map->board[xVal][yVal] = state;

    // Success!
    return 1;
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
        if (map->board[map->size - i - 1][i] == X)
            x++;
        if (map->board[map->size - i - 1][i] == Y)
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

TileListNode* getEmptyTiles(Map* map, int* size)
{
	// Variables
    int i, j;
    TileListNode *toDelete, *tmp, *retVal = NULL;
    TileListNode **currentNode;

    // Clear the size
    *size = 0;

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
                        // Loop through the list from start until end and delete the node.
                    	for (toDelete = retVal; toDelete != NULL;)
                    	{
                            tmp = toDelete->next;
                            free(toDelete);
                            toDelete = tmp;
                    	}

                    	// If there is a problem, clear the size.
                    	*size = 0;
                }

                // Fill out the map data
                (*currentNode)->x = i;
                (*currentNode)->y = j;
                (*currentNode)->next = NULL;

                // Advance the current node pointer to the new current node
                currentNode = &(*currentNode)->next;

                // Increase the size of the list.
                (*size)++;
            }
        }
    }

    // Return the result.
    return retVal;
}

int mapEquivalent(Map* a, Map* b)
{
    // Variables
    int i, j;

    // First, check that map sizes match
    if (a->size != b->size) return 0;

    // Loop through the board and compare the two maps
    for (i = 0; i < a->size; ++i)
    {
        for (j = 0; j< a->size; ++j)
        {
            // Return if not equivalent
            if (a->board[i][j] != b->board[i][j]) return 0;
        }
    }

    // They are equivalent
    return 1;
}

const char* mapToString(Map* m)
{
    // Variables
    int   mapSize, tmpSize, i, j;
    char  *mapString, *buff;

    // Calculate how much memory it takes for the string. Lets
    // start with the header size. There are <size> headers with
    // newlines and one without. The header is 2<size> + 1
    mapSize = (2 * m->size) + 1; // Calculate the size of a line of ticks
    mapSize *= (m->size + 1); // There are <size> + 1 headers
    mapSize += m->size; // There are <size> new lines because <size> headers end with one.

    // We can calculate the size of a line and then there are <size> number of them
    tmpSize = (m->size * 2) + 2; // A space and a | per element with an extra | and newline
    mapSize += (tmpSize * m->size); // There are <size> number of lines
    mapSize++; // We null terminate strings

    // Now lets make some memory
    mapString = (char*) malloc(sizeof(char) * mapSize);
    buff = (char*) malloc(sizeof(char) * 4);

    // Did that work?
    if (!mapString || !buff) return NULL;

    // Now, we'll load the tmpSize with the size of out ticks.
    tmpSize = (2 * m->size) + 1;

    for (i = 0; i < m->size; ++i)
    {
        // Add ticks
        for (j = 0; j < tmpSize; ++j)
        {
            strcat(mapString, "-");
        }
        strcat(mapString, "\n");

        for (j = 0; j < m->size; ++j)
        {
            if (m->board[i][j] == X || m->board[i][j] == Y)
            {
                sprintf(buff, "|%s", stateToString(m->board[i][j]));
                strcat(mapString, buff);
            }
            else
            {
                strcat(mapString, "| ");
            }
        }
        strcat(mapString, "|\n");
    }

    for (j = 0; j < tmpSize; ++j)
    {
        strcat(mapString, "-");
    }

    return mapString;
}

Map* deepCopy(Map* map)
{
    // Variables
    int i, j;
    Map* retVal;

    // Allocate the new map
    retVal = (Map*) malloc(sizeof(Map));

    // Did memory get allotted?
    if (!retVal) return NULL;

    // Copy the new size
    retVal->size = map->size;

    // Allocate board space
    retVal->board = (TileState **) malloc(sizeof(TileState *) * retVal->size);

    // Did board memory get allocated?
    if (!retVal->board)
    {
        // Delete the map
        free(retVal);
        return NULL;
    }

    // Now we'll step through and allocate the individual rows.
    for (i = 0; i < retVal->size; ++i)
    {
        // Allocate memory for the row.
        retVal->board[i] = (TileState *) malloc(sizeof(TileState) * retVal->size);

        // Check the validity of memory allocation.
        if (!retVal->board[i])
        {
            // There was an error, delete allocated rows.
            for (j = i - 1; j <= 0; --j)
            {
                free(retVal->board[j]);
            }

            // Delete the board pointer memory
            free(retVal->board);

            // Delete the map memory.
            free(retVal);
        }
    }

    // It looks like the memory was all set up correctly.
    // Now we copy the elements over.
    for (i = 0; i < retVal->size; ++i)
    {
        for (j = 0; j < retVal->size; ++j)
        {
            retVal->board[i][j] = map->board[i][j];
        }
    }

    // All done
    return retVal;
}

TileState toggleTileState(TileState state)
{
    // If the state is valid, toggle it.
    if (state == X) return Y;
    if (state == Y) return X;

    // If the state is not valid, NONE
    return NONE;
}
