#include "gui.h"

gui::gui(){
    vertexImage.loadFromFile("./assets/vertex.png");
    sans.loadFromFile("./assets/sans.ttf");
    vertex_center = 32;
    vertex_center_text = 24;
    window_res = {1024,1024};
    vInput_res = {300, 150};
    EdgeCount = 0;
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
        float x = r*cos(i*theta + PI/2) + center;
        float y = r*sin(i*theta + PI/2) + center;
        vertices[i].setPosition(x, y);
        num[i].setFont(sans);
        num[i].setString(std::to_string(i));
        num[i].setCharacterSize(15);
        num[i].setFillColor(sf::Color::Black);
        num[i].setPosition(x + vertex_center_text, y + vertex_center_text);
    }
}

void gui::addEdges(int u,int v, int w, Graph g){
    g.addEdge(u, v, w);
    ++EdgeCount;
}

void gui::addEdgesGUI(int V, std::list<iPair>* adj, Sprite guiVertex[], sf::Vertex line[][2]){
    int counter{};
    for (int i = 0; i < V; i++) {
        for (auto& x : adj[i]) {
            float x1 =guiVertex[i].getPosition().x + vertex_center;
            float y1 =guiVertex[i].getPosition().y + vertex_center;
            float x2 =guiVertex[x.first].getPosition().x + vertex_center;
            float y2 =guiVertex[x.first].getPosition().y + vertex_center;
            line[counter][0] = {{x1,y1}, Color::Black};
            line[counter][1] = {{x2,y2}, Color::Black};
            ++counter;
        }
    }
}

void gui::vertexInputGUI(int& V){
    sf::String playerInput;
    sf::Text playerText("",sans, 25);
    playerText.setPosition(Vector2f{35,50});
    playerText.setFillColor(sf::Color::Black);
    sf::Text numofVertices("Number of vertices:", sans, 30);
    numofVertices.setPosition(Vector2f{30,15});
    numofVertices.setFillColor(sf::Color::Black);
    RenderWindow window(sf::VideoMode({vInput_res.x, vInput_res.y}), "Input", Style::Titlebar|Style::Close);
    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();

            if (e.type == sf::Event::TextEntered){
                if (e.text.unicode > 47 && e.text.unicode < 58){
                    if(playerInput.getSize() < 16){
                        playerInput +=e.text.unicode;
                        playerText.setString(playerInput);
                    }
                }
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Backspace)){
                if(playerInput.getSize() > 0){
                    playerInput.erase(playerInput.getSize()-1, 1);
                    playerText.setString(playerInput);
                }
            }

            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Enter)){
                std::string ans_string = playerInput;
                V = std::stoi(ans_string);
                window.close();
            }

        }
        window.clear(sf::Color::White);
        window.setVerticalSyncEnabled(true);
        window.draw(numofVertices);
        window.draw(playerText);
        window.display();
    }
}

void gui::start(){

    int V{};
    vertexInputGUI(V);
    RenderWindow window(sf::VideoMode({window_res.x, window_res.y}), "Dijkstra", Style::Titlebar|sf::Style::Close);
    Sprite guiVertex[V];
    sf::Text vert_text[V];
    Graph g(V);
    initVertexSprite(V, guiVertex,vert_text);

    addEdges(0,1,6,g);
    addEdges(0,2,6,g);
    addEdges(0,3,6,g);
    addEdges(0,4,6,g);
    addEdges(1,2,6,g);
    addEdges(1,3,6,g);
    addEdges(1,4,6,g);
    addEdges(2,3,6,g);
    addEdges(2,4,6,g);
    addEdges(3,4,6,g);

  

    sf::Vertex line[2*EdgeCount][2];
    addEdgesGUI(V, g.getadj(), guiVertex, line);

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
        for(int i{}; i < 2*EdgeCount; ++i) window.draw(line[i], 2,sf::PrimitiveType::Lines);
        for(int i{}; i < V; ++i) window.draw(guiVertex[i]);
        for(int i{}; i < V; ++i) window.draw(vert_text[i]);
        window.display();

    }

}