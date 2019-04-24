#ifndef _TREE_H
#define _TREE_H

/**
 * Types Required to build a tree
 */
typedef struct TreeNode TreeNode;

/**
 * This represents a tree node. The goal of this
 * node is to be able to populate its child states
 * then to be able to score itself. These functions 
 * will be callbacks set by the user; so, no detail
 * about their content will be provided here.
 * 
 * @param scoreNode   (function *)  - The callback to score the node
 * @param numChildren (int)         - The number of child nodes
 * @param children    (TreeNode **) - The list of child nodes
 */
typedef struct TreeNode {
    void (*buildNode)(void *stateData);
    int (*scoreNode)(void *stateData);
    int numChildren; 
    TreeNode **children;
} TreeNode;

#endif