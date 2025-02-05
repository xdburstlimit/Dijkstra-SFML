#ifndef _GUI_
#define _GUI_
#include "graph.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

#define PI 3.141592653589793

class gui{
    private:
        Vector2u window_res;
        Texture vertexImage;
        float vertex_center;
        int EdgeCount;
        sf::Font sans;
    public:
        gui();
        ~gui() = default;
        Graph initGraph(int V);
        void initVertexSprite(int V, Sprite vertices[], sf::Text num[]);
        void addEdges(int u,int v, int w, Graph g);
        void buildGraph();
        void buildGraphGUI();
        void start();
};
#endif

