#include "gui.h"

gui::gui(){
    vertexImage.loadFromFile("./assets/vertex.png");
    sans.loadFromFile("./assets/sans.ttf");
    vertex_center = 32;
    vertex_center_text = 24;
    window_res = {1280,1024};
    vInput_res = {300, 150};
    EdgeCount = 0;
}


Graph gui::initGraph(int V){
    Graph g(V);
    return g;
}


void gui::initVertexSprite(int V,Sprite vertices[],  sf::Text num[]){
    
    float center= 512;
    float custom_x = center + 320;
    float r = 384;
    float circum = 2*PI*r;
    float arc = circum/float(V);
    float theta = arc/r;
    float pi2 = PI / 2;
    for(int i{}; i < V; ++i){
        vertices[i].setTexture(vertexImage);
        float x = r*cos(i*theta - PI/2) + custom_x;
        float y = r*sin(i*theta - PI/2) + center;
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

/*
    edgeInput GUI controls

    very rought at the moment

    Left Arrow: Move input to the left
    Right Arrow: Move input to the right
    Enter: To add an edge
    Escape: To display Graph
    Close window: To display Graph

    if invalid vertex
    when enter is pressed nothing happens
*/

void gui::edgeInputGUI(Graph& g, int V){
    sf::String uInput;
    sf::String vInput;
    sf::String wInput;
    int box_position{0};
    int u{};
    int v{};
    int w{};
    sf::Text uText("",sans, 25);
    uText.setPosition(Vector2f{35,50});
    uText.setFillColor(sf::Color::Black);

    sf::Text vText("",sans, 25);
    vText.setPosition(Vector2f{70,50});
    vText.setFillColor(sf::Color::Black);

    sf::Text wText("",sans, 25);
    wText.setPosition(Vector2f{105,50});
    wText.setFillColor(sf::Color::Black);

    sf::Text addEdges("Add Edge: ", sans, 30);
    addEdges.setPosition(Vector2f{30,15});
    addEdges.setFillColor(sf::Color::Black);
    RenderWindow window(sf::VideoMode({vInput_res.x, vInput_res.y}), "Input", Style::Titlebar|Style::Close);
    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();

            if((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Escape))
                window.close();

            if (e.type == sf::Event::TextEntered){
                if (e.text.unicode > 47 && e.text.unicode < 58){
                    if(uInput.getSize() < 2 && box_position == 0){
                        uInput +=e.text.unicode;
                        uText.setString(uInput);
                    }else if(vInput.getSize() < 2 && box_position == 1){
                        vInput +=e.text.unicode;
                        vText.setString(vInput);
                    }else if(wInput.getSize() < 3 && box_position == 2){
                        wInput +=e.text.unicode;
                        wText.setString(wInput);
                    }
                }
            }
            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Backspace)){
                if(uInput.getSize() > 0 && box_position == 0){
                    uInput.erase(uInput.getSize()-1, 1);
                    uText.setString(uInput);
                }else if(vInput.getSize() > 0 && box_position == 1){
                    vInput.erase(vInput.getSize()-1, 1);
                    vText.setString(vInput);
                }else if(wInput.getSize() > 0 && box_position == 2){
                    wInput.erase(wInput.getSize()-1, 1);
                    wText.setString(wInput);
                }
            }

            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Right)){
                if(box_position >= 0 && box_position < 3)
                    ++box_position;
                if(box_position == 3)
                    box_position = 0;
            }

            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Left)){
                if(box_position >= 0 && box_position < 3)
                    --box_position;
                if(box_position == -1)
                    box_position = 2;
            }


            if ((e.type == sf::Event::KeyPressed) && (e.key.code == sf::Keyboard::Enter)){
                std::string u_string = uInput;
                std::string v_string = vInput;
                std::string w_string = wInput;
                bool valid_vertex = (std::stoi(u_string) >= 0 && std::stoi(u_string) < V) && (std::stoi(v_string) >= 0 && std::stoi(v_string) < V);
                if(uInput != "", vInput!= "" && wInput != "" && valid_vertex){
                    u = std::stoi(u_string);
                    v = std::stoi(v_string);
                    w = std::stoi(w_string);
                    g.addEdge(u, v, w);

                    uInput.erase(uInput.getSize()-1, uInput.getSize());
                    uText.setString("");
                    vInput.erase(vInput.getSize()-1, vInput.getSize());
                    vText.setString("");
                    wInput.erase(wInput.getSize()-1, wInput.getSize());
                    wText.setString("");
                    box_position = 0;
                }
            }



        }
        window.clear(sf::Color::White);
        window.setVerticalSyncEnabled(true);
        window.draw(addEdges);
        window.draw(uText);
        window.draw(vText);
        window.draw(wText);
        window.display();
    }
}

/*
    TODO:
        gui start
        -add edge lengths to graph(take vertex positions and subtract for existing neighbours and divide by two so that you can place value in the middle of the edge)
        -improve results table(add paths taken, what vertex in the set)

        Vertex input:
        -add more visuals

        Source node Box:
        -add this

        EdgeInput:
        -maybe add more keys to navigate the boxes
        -add more visuals
        -add another button to display the final graph
        -add a temporary display of graph being built(?)
        -show what edges have been added
 
*/


void gui::start(){

    int V{};
    vertexInputGUI(V);
    Sprite guiVertex[V];
    sf::Text vert_text[V];
    Graph g(V);
    initVertexSprite(V, guiVertex,vert_text);

    edgeInputGUI(g,V);
    EdgeCount = g.countEdges(V, g.getadj());
    sf::Vertex line[2*EdgeCount][2];


    addEdgesGUI(V, g.getadj(), guiVertex, line);

    RenderWindow window(sf::VideoMode({window_res.x, window_res.y}), "Dijkstra", Style::Titlebar|sf::Style::Close);
    std::vector <int> dist(V,INF);
    g.shortestPath(0,dist);
    sf::String dist_string[V];
    for(int i{}; i < V; ++i){
        dist_string[i] = std::to_string(dist[i]);
        if(dist[i]==INF)
            dist_string[i] = "INF";
    }

    
    sf::Text dist_text[V];

    for(int i{}; i < V; ++i){
        dist_text[i].setString(dist_string[i]);
        dist_text[i].setFont(sans);
        dist_text[i].setPosition(Vector2f{35,float(i)*50});
        dist_text[i].setFillColor(sf::Color::Black);

    }
        


    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed)
                window.close();
        }
        window.clear(sf::Color::White);
        window.setVerticalSyncEnabled(true);
        for(int i{}; i < 2*EdgeCount; ++i) window.draw(line[i], 2,sf::PrimitiveType::Lines);
        for(int i{}; i < V; ++i) window.draw(guiVertex[i]);
        for(int i{};i < V; ++i) window.draw(dist_text[i]);
        for(int i{}; i < V; ++i) window.draw(vert_text[i]);
        window.display();

    }

}