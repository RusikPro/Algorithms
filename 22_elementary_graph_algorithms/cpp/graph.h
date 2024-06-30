#ifndef __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_GRAPH_H__
#define __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_GRAPH_H__

/*----------------------------------------------------------------------------*/

#include "constants.h"

#include <list>
#include <string>

/*----------------------------------------------------------------------------*/

enum class Color
{
    White,
    Gray,
    Black
};

/*----------------------------------------------------------------------------*/

struct Node
{
    std::list< Node * > adjacencyList;
    Color color;
    int distance = MAXIMUM;
    Node * pPredecessor = nullptr;
    char c;
};

/*----------------------------------------------------------------------------*/

#endif // __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_GRAPH_H__