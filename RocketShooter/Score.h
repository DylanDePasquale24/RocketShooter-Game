#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "TextureManager.h"
#include "Enemys.h"
using std::vector;
using std::string;
using std::cout;

class Score
{

	unsigned long long score;
	vector<sf::Sprite> digitVec;       //<digit1,digit2,digit3>   (goes left to right)     so if score= 100 --> <1,0,0>
	const int scoreInterval = 100;     // milliseconds
	bool maxScoreReached;

	sf::Sprite scrSprite;
	const int yPos = 25;
	const int yPosComma = 40;
	const int xPosStart = 135;
	const int xOffset = 24;  //for each additional Digit

	const int distanceIncrement = 1;  //score you increase by every second (for distance)

public:
	Score();

	void Reset();
	void Draw(sf::RenderWindow& window);
	void DrawOnEndScreen(sf::RenderWindow& window);

	int GetScoreInterval();
	void IncrementDistance();
	void IncrementEnemy(Enemy* enemy, int wave);

private:
	void UpdateDigits();
	void DrawDigits(sf::RenderWindow& window);
	void DrawMaxScore(sf::RenderWindow& window);
};


