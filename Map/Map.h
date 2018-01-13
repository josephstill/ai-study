/**
 * This marks the state of a tile on the game map and state of the overall game.
 */
typedef enum TileState
{
	NONE = 0x0,
	X    = 0x1,
	Y    = 0x2,
	TIE  = 0x3
} TileState;

/**
 * This represents a game map. The game map will be a
 * variable size which contains an array of tile states and
 * and a size dimension. The map will also have a winner
 * marker that will report the current state of the game
 *
 * The size is the dimension of the game board. The board
 * Will always be a perfect square with the goal being to
 * reach <size> number of elements in a row or diagonal
 *
 * The board will be a multidimensional and contain the
 * tile states. Its dimensions are <size> x <size>
 *
 * @param board: (TileState **) - The state of the map
 * @param size:  (int)          - The dimensions of the map
 */
typedef struct Map
{
	TileState** board;
	int size;
} Map;

/**
 * We will want a linked list to return for empty tiles
 */
typedef struct TileListNode TileListNode;

/**
 * This list node describes a position on the game map.
 *
 * @param x: The x position.
 * @param y: The y position.
 * @param next: A pointer to the next node.
 */
struct TileListNode
{
    int x;
    int y;
    TileListNode* next;
} ;

/**
 * Initializes a map object of the given size.
 *
 * @param size: The size of the map to create
 * @return: A pointer to the new map or NULL if the process failed.
 */
Map* createMap(int size);

/**
 * Deletes the map that was passed in.
 *
 * @param map: The map to delete
 */
void deleteMap(Map* map);

/**
 * Prints a string representation of the tile state.
 *
 * @param state: The tile state
 * @return: A string representation of the tile state
 */
const char* stateToString(TileState state);

/**
 * Sets the state of the specified game space to the provided state.
 * If (x, y) is invalid coordinates, then the finction will return 0.
 *
 * @param map:   The map to operate on.
 * @param xVal:  The x coordinate to set.
 * @param yVal:  The y coordinate to set.
 * @param state: The state to set.
 * @return: 1 for success, 0 for bad coordinates, -1 for bad state
 */
int setMapState(Map* map, int xVal, int yVal, TileState state);

/**
 * Tests the map for a winner. If there is no winner, NONE is returned.
 *
 * @param map: The map to test for a winner.
 * @return: The winner or NONE
 */
TileState determineMapWinner(Map* map);

/**
 * Search the map for empty positions. Ownership of the returned list
 * is transferred to the caller; so, freeing memory is a must to prevent leaks.
 * If the map is full, NULL is returned.
 *
 * @param map: The map to search.
 * @return: The pointer to the head of a linked list.
 */
TileListNode* getEmptyTiles(Map* map);

/**
 * Checks maps for their equivalency. If the maps are equivalent 1 is returned
 * otherwise 0 is returned.
 *
 * @param a: The first map to check against.
 * @param b: The second map to check against.
 * @return: 1 for equivalent and 0 for not equivalent
 */
int mapEquivalent(Map* a, Map* b);

/**
 * Returns a string representation of the map.
 *
 * @param m: The map to produce a string of.
 * @return: A string representation of the map.
 */
const char* mapToString(Map m);


