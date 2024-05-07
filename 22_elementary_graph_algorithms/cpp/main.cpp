#include "graph.h"

#include <iostream>

int main ()
{
    std::cout << "Hello from main in 22_elementary_graph_algorithms" << std::endl;

    Node * graph = createGraphByFigure_22_3();

    std::cout << "r: letter - " << graph[ 0 ].c
        << " size - " << graph[ 0 ].adjacencyList.size() << std::endl
    ;

    delete [] graph;

    return 0;
}
