#include <bits/stdc++.h>
#include <vector>
#define INF 10000000
#define V 9

void dijkstra(int length[V][V], int dist[V],int source);
void addEdge(int length[V][V],int u, int v, int w);
int minDistIndex(int dist[V]);
void printGraph(int length[V][V]);
bool validRange(int u, int v);
void printResults(int dist[V]);

int main(){
    std::vector<int> Q;
    int dist[V];
    int length[V][V] ={ { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    //addEdge(length, 0, 4, 3);
    
    //printGraph(length);
    //std::cout << minDistIndex(dist) << '\n';
    for(int i{0}; i < V; ++i){
        dist[i] = INF;
    }

    dist[4] = 0;
    std::cout << minDistIndex(dist) << '\n';
    //dijkstra(length,dist,0);
   //printResults(dist);

    
    //(label, dist)

}

void printResults(int dist[V]){
    std::cout << "From Source" << std::setw(10) << "Distance\n";
    for(int i{}; i < V; ++i){
        std::cout << i << std::setw(10) << dist[i] << '\n';
    }
}

void dijkstra(int length[V][V], int dist[V],int source){
    std::vector<int> Q;
    for(int i{}; i < V; ++i){
        dist[i] = INF;
        Q.push_back(i);
    }
    dist[source] = 0;

    while(!Q.empty()){
        int v = minDistIndex(dist);
        Q.erase(Q.begin() + v);
        for(int u{}; u < V; ++u){
            int alt = dist[v] + length[v][u];
            if(alt < dist[u])
                dist[u] = alt;
            
        }

    }

}

int minDistIndex(int dist[V]){
    int min = dist[0];
    int mp{};
    for(int i{}; i < V; ++i){
        int curr = dist[i];
        if(curr < min){
            mp = i;
            min = curr;
        }
    }


    return mp;
}

void addEdge(int length[V][V],int u, int v, int w){
    if(validRange(u,v)){
        length[u][v] = w;
        length[v][u] = w;
    }else{
        std::cerr << "Attempted to add an invalid edge.\n";
    }
}

bool validRange(int u, int v){
    if((u >= 0 && u < V) && (v >= 0 && v < V)){
        return true;
    }
    return false;
}

void printGraph(int length[V][V]){
    for(int i{}; i < V; ++i){
        for(int j{}; j < V; ++j){
            std::cout << length[i][j] << std::setw(3);
        }
        std::cout << '\n';
    }
}
