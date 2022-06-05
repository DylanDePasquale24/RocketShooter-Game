#pragma once
#include <vector>
#include <iostream>
#include "Asteroid.h"
#include "Wave.h"
using std::vector;
using std::cout;

class Asteroids
{
	vector<Asteroid> astroidVec;

public:
	Asteroids();

	void UpdatePositions();
	void CreateAsteroid(Wave& wave);
	void Draw(sf::RenderWindow& window);
	void Reset();
};

