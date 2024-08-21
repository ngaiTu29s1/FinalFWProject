#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SetupGraph.h"

struct DPManager
{
	sf::Texture DPtexture;
	sf::Texture Maintexture;
	sf::Texture Randomtexture;
	sf::Texture Manualtexture;
	sf::Texture RunTexture;

	sf::Sprite DPsprite;
	sf::Sprite Mainsprite;
	sf::Sprite Randomsprite;
	sf::Sprite Manualsprite;
	sf::Sprite RunSprite;

	void setDisplay();

	void setMainDP();

	void setRandomMode();

	void setManualMode();

	void setRunDP();

	void setSprite(sf::Sprite& dp, sf::Sprite& main, sf::Sprite& random, sf::Sprite& manual, sf::Sprite& runDP);
};

void setBackground(sf::RenderWindow& window, sf::Sprite& background, sf::Texture& texture);

void inputConvert(std::string input, int& num, int& start, int& end);

void drawGraph(sf::RenderWindow& window, std::vector<sf::CircleShape>& graph, std::vector<sf::Text>& vertices, std::vector<std::vector<line>> lines_list, int num);