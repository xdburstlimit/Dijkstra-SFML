#include "graph.h"

Graph::Graph(int V){
    this->V = V;
    adj = new std::list<iPair>[V];  //vertex and weight 
}

void Graph::addEdge(int u, int v, int w){
    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
}

void Graph::shortestPath(int source){
    std::priority_queue <iPair,std::vector<iPair>, std::greater<iPair>> pq;

    std::vector <int> dist(V,INF);
    std::vector <int> path(V, source);
    pq.push({source,0});
    dist[source] = 0;

    while(!pq.empty()){
        int u = pq.top().first;
        pq.pop();

        for(auto neighbour:adj[u]){//iterate all neighbours v around u
            int v = neighbour.first;
            int w = neighbour.second;
            if(dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                pq.push({v,dist[v]});
            }

        }

    }
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

int Graph::countEdges(int V,std::list<iPair>* adjL){
    int count{};
    for (int i = 0; i < V; i++) {
        for (auto& x : adjL[i]) {
            ++count;
        }
    }
    return (count/2);
}