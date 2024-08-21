#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
public:
    TextBox(float x, float y, float width, float height);

    void handleInput(sf::Event event);

    void draw(sf::RenderWindow& window);

    std::string getContent() const;

    bool isInputActive() const;

    void clear();

private:
    sf::RectangleShape background;
    sf::Text displayText;
    sf::Font font;
    std::string content;
    bool isActive;
};