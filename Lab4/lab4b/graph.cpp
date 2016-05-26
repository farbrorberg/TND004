/*********************************************
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Graph::Graph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Graph::~Graph()
{
    delete[] array;
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
    array[v].insert(u, w);
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
    array[v].remove(u);
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const
{
    bool *done = new bool[size + 1];;
    for(int idx = 0; idx <= size; idx++)
    {
        done[idx] = false;
    }

    int node_nr = 1;
    Node *p;

    Heap<Edge> h;
    Edge minEdge;
    int counter = 1;
    int totWeight = 0;

    do
    {
        counter++;
        done[node_nr] = true;
        p = array[node_nr].getFirst();
        while(p)
        {

            h.insert(Edge(node_nr, p->vertex ,p->weight ));
            p = p->next;
        }

        do
        {
            minEdge = h.deleteMin();
        }
        while(done[minEdge.head] && done[minEdge.tail]);

        totWeight += minEdge.weight;
        cout << minEdge << endl;
        node_nr = minEdge.tail;
    }
    while(counter < size);

    cout << endl << "Total weight = " << totWeight << endl;

}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const
{
    bool *done = new bool[size + 1];;
    for(int idx = 0; idx <= size; idx++)
    {
        done[idx] = false;
    }

    Heap<Edge> h;
    Node *p = array[1].getFirst();

    //Fill the heap with all edges
    int idx = 1;
    while(idx <= size)
    {
        h.insert(Edge(idx, p->vertex ,p->weight ));
        p = p->next;

        if(!p)
        {
            idx++;
            if(idx <= size)
                p = array[idx].getFirst();
        }
    }

    Edge minEdge;
    DSets dis(size);
    int counter = 0;
    int totWeight = 0;

    while(counter < size-1)
    {
        minEdge = h.deleteMin();
//        cout << "Kasta? " << minEdge << endl;
//
//        cout << "find(minEdge.head): " << dis.find(minEdge.head) << endl;
//        cout << "find(minEdge.tail): " << dis.find(minEdge.tail) << endl;

        if(dis.find(minEdge.head) != dis.find(minEdge.tail))
        {

            dis.join(dis.find(minEdge.tail),dis.find(minEdge.head));

            totWeight += minEdge.weight;
            counter++;
            cout << minEdge << endl;
        }
    }
    cout << endl <<"Total weight = " << totWeight << endl;
}

// print graph
void Graph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                                            " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}
