#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include "SetupGraph.h"
#include "SetupDisplay.h"
#include "TextBox.h"

#define WINDOW_HEIGHT 1600
#define WINDOW_WIDTH 900

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "SHORTEST PATH");
	sf::Texture texture;
	sf::Sprite background;
	setBackground(window, background, texture);
    window.setFramerateLimit(60);

    std::vector<sf::CircleShape> graph;
    std::vector<sf::Text> vertices;
    std::vector<std::vector<line>> lines_list;
    Matrix matrix;
    sf::Sprite runner_sprite, notFoundSprite;
    sf::Sprite dp, mainDP, randomDP, manualDP, runDP;

    sf::Font font;
    while (!font.loadFromFile("ARIAL.TTF")) {
        std::cout << "Error";
        return -1;
    }

    sf::Texture runner_texture, notFoundTexture;
    while (!runner_texture.loadFromFile("Pictures/runner.png")) {
        std::cout << "Error!";
        return -1;
    }
	while (!notFoundTexture.loadFromFile("Pictures/notfound.png")) {
		std::cout << "Error!";
		return -1;
	}


    DPManager dpManager;
    dpManager.setSprite(dp, mainDP, randomDP, manualDP, runDP);

    bool implemented = 0; //init background and matrix
    bool scanned = 0; //scan vertices, start, end

    int num_vertices = 0, start = 0, end = 0;

    TextBox inputBox(385, 285, 80, 30);

    while (window.isOpen()) {
        static sf::Event event;
        static sf::Sprite nowBackground = dp;
        static bool CPressed = 0, num1Pressed = 0, num2Pressed = 0, inputScanned = 0;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B) {
					nowBackground = dp;
                }
                else if (event.key.code == sf::Keyboard::C) {
                    nowBackground = mainDP;
					CPressed = 1;
                }
                else if (event.key.code == sf::Keyboard::Num1 && CPressed) {
                    nowBackground = runDP;
                    num1Pressed = 1;
                    CPressed = 0;
                    nowBackground = randomDP;
                }
                else if (event.key.code == sf::Keyboard::Num2 && CPressed) {
                    nowBackground = runDP;
					num2Pressed = 1;
                    CPressed = 0;
					nowBackground = manualDP;
                }
            }
            if (num1Pressed || num2Pressed) {
                inputBox.handleInput(event);
                window.display();

                if (!inputBox.isInputActive()) {
                    inputScanned = 1;
                }
            }
        }
        
        window.draw(nowBackground);

        if (implemented == 0 && inputScanned) {
			inputConvert(inputBox.getContent(), num_vertices, start, end);
            matrix.vertex = num_vertices;
			if (num1Pressed) matrix.create();
            else if(num2Pressed) matrix.read("matrix.txt");
            matrix.print();
            matrix.find(start, end);
            set_graph(graph, num_vertices);
            set_vertices(vertices, graph, font, num_vertices);
            set_lines(lines_list, graph, num_vertices, font, matrix);

            runner_texture.setSmooth(true);
            runner_sprite.setTexture(runner_texture);
            runner_sprite.setPosition(graph[start].getPosition());

            notFoundTexture.setSmooth(true);
			notFoundSprite.setTexture(notFoundTexture);
			notFoundSprite.setPosition(0, 0);

            implemented = 1;
        }

 
         
        if (nowBackground.getTexture() == randomDP.getTexture() || nowBackground.getTexture() == manualDP.getTexture())
        {
            if (num1Pressed || num2Pressed) {
                inputBox.draw(window);
            }

			drawGraph(window, graph, vertices, lines_list, num_vertices);

            window.draw(runner_sprite);

            if (inputScanned) {
                if (matrix.path.size() < 2) {
					window.draw(notFoundSprite);
                }
                else
                {
					run(&runner_sprite, graph, matrix.path);
                }
            }
        }
        window.display();
    }
    return 0;
}

