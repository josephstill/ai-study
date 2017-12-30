/**
 * This marks the state of a tile on the game map.
 */
typedef enum TileState
{
	NONE = 0x0,
	X    = 0x1,
	Y    = 0x2
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
	//TODO add size variable
} Map;

/**
 * Initializes a map object of the given size.
 *
 * @param size: The size of the map to create
 * @return: A pointer to the new map or NULL if the process failed.
 */
Map* createMap(int size);


