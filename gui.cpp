#include "gui.h"

gui::gui(){
    vertexImage.loadFromFile("./assets/vertex.png");
    sans.loadFromFile("./assets/sans.ttf");
    vertex_center = 24;
    window_res = {1024,1024};
}


Graph gui::initGraph(int V){
    Graph g(V);
    return g;
}


void gui::initVertexSprite(int V,Sprite vertices[],  sf::Text num[]){
    float center= 512;
    float r = 384;
    float circum = 2*PI*r;
    float arc = circum/float(V);
    float theta = arc/r;
    for(int i{}; i < V; ++i){
        vertices[i].setTexture(vertexImage);
        float x = r*cos(i*theta) + center;
        float y = r*sin(i*theta) + center;
        vertices[i].setPosition(x, y);
        num[i].setFont(sans);
        num[i].setString(std::to_string(i));
        num[i].setCharacterSize(15);
        num[i].setFillColor(sf::Color::Black);
        num[i].setPosition(x + vertex_center, y + vertex_center);
    }
}

void gui::addEdges(int u,int v, int w, Graph g){
    g.addEdge(u, v, w);
}

void gui::start(){

    RenderWindow window(sf::VideoMode({window_res.x, window_res.y}), "Dijkstra", Style::Titlebar|sf::Style::Close);
    int V = 25;
    Sprite guiVertex[V];
    sf::Text vert_text[V];
    Graph g(V);
    initVertexSprite(V, guiVertex,vert_text);
    float x1 =guiVertex[0].getPosition().x + vertex_center;
    float y1 =guiVertex[0].getPosition().y + vertex_center;
    float x2 =guiVertex[5].getPosition().x + vertex_center;
    float y2 =guiVertex[5].getPosition().y + vertex_center;
    g.addEdge(0,5,6);
    float x3 =guiVertex[10].getPosition().x + vertex_center;
    float y3 =guiVertex[10].getPosition().y + vertex_center;
    float x4 =guiVertex[15].getPosition().x + vertex_center;
    float y4 =guiVertex[15].getPosition().y + vertex_center;
    g.addEdge(10,15,6);
    EdgeCount = g.countEdges(V, g.getadj());
    std::cout << EdgeCount << '\n';
    sf::Vertex line[][EdgeCount] = {{{{x1,y1}, Color::Black}, {{x2,y2}, Color::Black}}, {{{x3,y3}, Color::Black}, {{x4,y4}, Color::Black}}};
    

    /*
        TODO:
            connect the edges goddamnit

    */
    while(window.isOpen()){
        Vector2i pos = Mouse::getPosition(window);
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.setVerticalSyncEnabled(true);
        for(int i{}; i < 2; ++i) window.draw(line[i], 2,sf::PrimitiveType::Lines);
        for(int i{}; i < V; ++i) window.draw(guiVertex[i]);
        for(int i{}; i < V; ++i) window.draw(vert_text[i]);
        window.display();

    }

}