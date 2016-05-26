/*********************************************
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: mplementation of directed graphs   *
* file for students                          *
**********************************************/


#include <iostream>
#include <iomanip>
#include <cassert>
#include <stack>

using namespace std;

#include "digraph.h"
#include "queue.h"

const int INFINITY = 9999;

// -- CONSTRUCTORS

Digraph::Digraph(int n)
{
    assert(n >= 1);
    array = new List[n + 1];
    dist  = new int [n + 1];
    path  = new int [n + 1];
    done  = new bool[n + 1];
    size  = n;
}

// -- DESTRUCTOR

Digraph::~Digraph()
{
    delete[] array;
    delete[] dist;
    delete[] path;
    delete[] done;
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].insert(v, w);
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v)
{
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    array[u].remove(v);
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }

    Queue<int> Q;

    for(int idx = 1; idx <= size; idx++)
    {
        dist[idx] = INFINITY;
        path[idx] = 0;
        done[idx] = false;
    }

    dist[s] = 0;
    done[s] = true;
    Q.enqueue(s);

    while(!Q.isEmpty())
    {
        int current = Q.getFront();
        Q.dequeue();
        Node *temp = array[current].getFirst();
        while(temp)
        {
            if( done[temp->vertex] == false )
            {
                dist[temp->vertex] = dist[current]+1;
                path[temp->vertex] = current;
                Q.enqueue(temp->vertex);
                done[temp->vertex] = true;
            }
            temp = temp->next;
        }
    }
}

// positive weighted single source shortest pats
void Digraph::pwsssp(int s)
{
    if (s < 1 || s > size)
    {
         cout << "\nERROR: expected source s in range 1.." << size << " !" << endl;
         return;
    }
    Queue<int> Q;

    for(int idx = 1; idx <= size; idx++)
    {
        dist[idx] = INFINITY;
        path[idx] = 0;
        done[idx] = false;
    }

    dist[s] = 0;
    done[s] = true;
    Q.enqueue(s);

    while(!Q.isEmpty())
    {

        int current = Q.getFront();
        Q.dequeue();
        Node *temp = array[current].getFirst();
        while(temp)
        {
                if(dist[temp->vertex] > dist[current] + temp->weight)
                {
                        dist[temp->vertex] = dist[current]+temp->weight;
                        path[temp->vertex] = current;
                        Q.enqueue(temp->vertex);
                }
            //done[temp] = true;
            temp = temp->next;
        }
    }
}

// print graph
void Digraph::printGraph() const
{
    cout << "------------------------------------------------------------------" << endl;
    cout << "vertex  adjacency list                  " << endl;
    cout << "------------------------------------------------------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " : ";
        array[v].print();
    }

    cout << "------------------------------------------------------------------" << endl;
}

// print shortest path tree for s
void Digraph::printTree() const
{
    cout << "----------------------" << endl;
    cout << "vertex    dist    path" << endl;
    cout << "----------------------" << endl;

    for (int v = 1; v <= size; v++)
    {
        cout << setw(4) << v << " :" << setw(8) << dist[v] << setw(8) << path[v] << endl;
    }

    cout << "----------------------" << endl;
}

// print shortest path from s to t
void Digraph::printPath(int t) const
{
    if (t < 1 || t > size)
    {
         cout << "\nERROR: expected target t in range 1.." << size << " !" << endl;
         return;
    }

    stack<int> shortest_path;
    shortest_path.push(t);
    int start = t;

    while(path[t] != 0)
    {
        t = path[t];
        shortest_path.push(t);
    }

    while(!shortest_path.empty())
    {
        cout << " " << shortest_path.top() << " ";
        shortest_path.pop();
    }
    cout << "(" << dist[start] << ")" << endl;
}
