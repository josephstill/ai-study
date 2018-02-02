#ifndef _TREE_H
#define _TREE_H

#include "../Map/Map.h"

/**
 * This struct defines an individual node in the winner tree
 */
typedef struct WinnerTreeNode WinnerTreeNode;

/**
 * This structure defines the node for the winner tree. Winner trees will be passed around as pointers
 * to the current root node. The root node does not necessarily have to be the empty map node, but the
 * node for the current state of the game.
 *
 * @param map: The map that represents the current state of the game.
 * @param children: A list of possible states to follow this one.
 * @param player: The player that is being considered for this tree.
 * @param wins: The number of winning paths from this state.
 * @param losses: The number of loss path from this state.
 * @param draws: The number of draw paths from this state.
 */
struct WinnerTreeNode
{
    Map* map;
    WinnerTreeNode* children;
    TileState player;
    int wins;
    int losses;
    int draw;
};




#endif
