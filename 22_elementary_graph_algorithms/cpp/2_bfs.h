#ifndef __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_2_BFS_H__
#define __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_2_BFS_H__

/*----------------------------------------------------------------------------*/

#include "graph.h"

#include <queue>

/*----------------------------------------------------------------------------*/

Node * getByLetter( Node * _graph, std::size_t _size, char _c )
{
    for ( std::size_t i = 0; i < _size; ++i )
    {
        if ( _graph[ i ].c == _c )
        {
            return _graph + i;
        }
    }

    return nullptr;
}

/*----------------------------------------------------------------------------*/

void bfs ( Node * _graph, std::size_t _size, Node * _s )
{
    for ( std::size_t i = 0; i < _size; ++i )
    {
        if ( _graph[ i ].c == _s->c ) continue;

        _graph[ i ].color = Color::White;
    }

    _s->color = Color::Gray;
    _s->distance = 0;
    _s->pPredecessor = nullptr;

    std::queue< Node * > Q;
    Q.push( _s );

    while ( !Q.empty() )
    {
        Node * u = Q.front();
        Q.pop();

        Node * current = getByLetter( _graph, _size, u->c );

        if ( !current ) continue;

        for ( Node * v: current->adjacencyList )
        {
            if ( v->color == Color::White )
            {
                v->color = Color::Gray;
                v->distance = u->distance + 1;
                v->pPredecessor = u;

                Q.push( v );
            }
        }

        u->color = Color::Black;
    }
}

/*----------------------------------------------------------------------------*/

#endif // __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_2_BFS_H__