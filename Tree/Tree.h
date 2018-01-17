#ifndef _TREE_H
#define _TREE_H

#include "../Map/Map.h"

/**
 *
 */
typedef struct WinnerTreeNode WinnerTreeNode;

/**
 *
 *
 * @param map:
 * @param children:
 * @param player:
 * @param wins:
 * @param losses:
 */
struct WinnerTreeNode
{
    Map* map;
    WinnerTreeNode* children;
    TileState player;
    int wins;
    int losses;
};


#endif
