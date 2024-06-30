#ifndef __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_2_BFS_H__
#define __22_ELEMENTARY_GRAPH_ALGORITHMS_CPP_2_BFS_H__

/*----------------------------------------------------------------------------*/

#include "graph.h"

#include <queue>

/*----------------------------------------------------------------------------*/

/*
struct Node
{
    std::list< Node * > adjacencyList;
    Color color;
    int distance = MAXIMUM;
    Node * pPredecessor = nullptr;
    char c;
};
*/

/*----------------------------------------------------------------------------*/

Node * createGraphByFigure_22_3 ()
{
    // Allocating array for all nodes
    Node * adjList = new Node[ 8 ];

    // Assigning letters to each vertex
    Node * r = adjList;     r->c = 'r';
    Node * v = adjList + 1; v->c = 'v';
    Node * s = adjList + 2; s->c = 's';
    Node * w = adjList + 3; w->c = 'w';
    Node * t = adjList + 4; t->c = 't';
    Node * x = adjList + 5; x->c = 'x';
    Node * u = adjList + 6; u->c = 'u';
    Node * y = adjList + 7; y->c = 'y';

    // Constructing graph

    r->adjacencyList.push_back( s );
    r->adjacencyList.push_back( v );

    v->adjacencyList.push_back( r );

    s->adjacencyList.push_back( w );
    s->adjacencyList.push_back( r );

    w->adjacencyList.push_back( t );
    w->adjacencyList.push_back( x );

    t->adjacencyList.push_back( u );
    t->adjacencyList.push_back( x );
    t->adjacencyList.push_back( w );

    x->adjacencyList.push_back( t );
    x->adjacencyList.push_back( u );
    x->adjacencyList.push_back( y );
    x->adjacencyList.push_back( w );

    u->adjacencyList.push_back( y );
    u->adjacencyList.push_back( x );
    u->adjacencyList.push_back( t );

    y->adjacencyList.push_back( u );
    y->adjacencyList.push_back( x );

    return adjList;
}

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

        for ( Node * v: u->adjacencyList )
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