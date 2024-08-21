#include "SetupDisplay.h"


void DPManager::setDisplay()
{
	if (!DPtexture.loadFromFile("Pictures/HelloDisplay.png")) {
		std::cout << "Error!";
		return;
	}
	DPsprite.setTexture(DPtexture);
	DPtexture.setSmooth(true);
}

void DPManager::setMainDP() 
{
	if (!Maintexture.loadFromFile("Pictures/MainMenu.png")) {
		std::cout << "Error!";
		return;
	}
	Mainsprite.setTexture(Maintexture);
	Maintexture.setSmooth(true);
}

void DPManager::setRandomMode() {
	if (!Randomtexture.loadFromFile("Pictures/RandomMode.png")) {
		std::cout << "Error!";
		return;
	}
	Randomsprite.setTexture(Randomtexture);
	Randomtexture.setSmooth(true);
}

void DPManager::setManualMode() {
	if (!Manualtexture.loadFromFile("Pictures/ManualMode.png")) {
		std::cout << "Error!";
		return;
	}
	Manualsprite.setTexture(Manualtexture);
	Manualtexture.setSmooth(true);
}

void DPManager::setRunDP() {
	if (!RunTexture.loadFromFile("Pictures/runBackground.png")) {
		std::cout << "Error!";
		return;
	}
	RunSprite.setTexture(RunTexture);
	RunTexture.setSmooth(true);
}


void DPManager::setSprite(sf::Sprite& dp, sf::Sprite& main, sf::Sprite& random, sf::Sprite& manual, sf::Sprite& runDP) {
	setDisplay();
	dp = DPsprite;
	setMainDP();
	main = Mainsprite;
	setRandomMode();
	random = Randomsprite;
	setManualMode();
	manual = Manualsprite;
	setRunDP();
	runDP = RunSprite;
}

void setBackground(sf::RenderWindow& window, sf::Sprite& background, sf::Texture& texture) {
	if (!texture.loadFromFile("Pictures/Background.png")) {
		std::cout << "Error!";
		return;
	}
	background.setTexture(texture);
	window.draw(background);
}

void inputConvert(std::string input, int& num, int& start, int& end)
{
	std::vector<int> nums;
	for (int i = 0; i < input.length(); i++)
	{
		std::string temp = "";
		while (input[i] != ' ' && i < input.length())
		{
			temp += input[i];
			i++;
		}
		nums.push_back(std::stoi(temp));
	}
	num = nums[0];
	start = nums[1];
	end = nums[2];
}

void drawGraph(sf::RenderWindow& window, std::vector<sf::CircleShape>& graph, std::vector<sf::Text>& vertices, std::vector<std::vector<line>> lines_list, int num) {
	for (auto x : graph) {
		window.draw(x);
	}
	for (auto y : vertices) {
		window.draw(y);
	}
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			window.draw(lines_list[i][j].edge);
			window.draw(lines_list[i][j].text_w);
		}
	}
}