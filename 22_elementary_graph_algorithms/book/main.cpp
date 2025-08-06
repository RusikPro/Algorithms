#include "2_bfs.h"

#include <iostream>

int main ()
{
    std::cout << "Hello from main in 22_elementary_graph_algorithms" << std::endl;

    Node * graph = createGraphByFigure_22_3();

    std::cout << "r: letter - " << graph[ 0 ].c
        << " size - " << graph[ 0 ].adjacencyList.size() << std::endl
    ;

    Node * s = graph + 2;
    bfs( graph, 8, s );

    std::cout << "graph[ 0 ].distance: " << graph[ 0 ].distance << std::endl;
    std::cout << "graph[ 1 ].distance: " << graph[ 1 ].distance << std::endl;
    std::cout << "graph[ 3 ].distance: " << graph[ 3 ].distance << std::endl;
    std::cout << "graph[ 4 ].distance: " << graph[ 4 ].distance << std::endl;
    std::cout << "graph[ 7 ].distance: " << graph[ 7 ].distance << std::endl;

    delete [] graph;

    return 0;
}
