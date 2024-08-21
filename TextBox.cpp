#include "TextBox.h"

TextBox::TextBox(float x, float y, float width, float height)
{
	isActive = true;
    background.setPosition(x, y);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::White);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    if (!font.loadFromFile("ARIAL.TTF")) {
		std::cout << "Error loading font\n";
        return;
    }

    displayText.setFont(font);
    displayText.setCharacterSize(18);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(x + 5, y + 5);
}

void TextBox::handleInput(sf::Event event) {
    if (!isActive) return;
    
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 13) { // Enter key
            isActive = false;
            background.setOutlineColor(sf::Color(128, 128, 128));
        }
        else if (event.text.unicode == 8 && !content.empty()) { // Backspace
            content.pop_back();
        }
        else if (event.text.unicode < 128) {
            content += static_cast<char>(event.text.unicode);
        }
        displayText.setString(content);
    }
}

void TextBox::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(displayText);
}

std::string TextBox::getContent() const {
    return content;
}

bool TextBox::isInputActive() const {
    return isActive;
}

void TextBox::clear() {
    content.clear();
    displayText.setString(content);
}