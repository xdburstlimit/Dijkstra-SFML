#ifndef _GRAPH_
#define _GRAPH_

#include <queue>
#include <list>
#include <vector>
#include <cstdio>
#include <string>
#include <iostream>

#define INF 0x3f3f3f3f

typedef std::pair<int, int> iPair;

class Graph{
    private:
        int V;
        std::list<iPair>* adj;
    public:
        Graph(int V);
        void addEdge(int u, int v, int w);
        void shortestPath(int s);
        int countEdges(int V,std::list<iPair>* adjL);
        std::list<iPair>* getadj(){return adj;}
        int getnV(){ return V; } //returns number of vertices

};

#endif