#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Wave : public sf::Sprite
{
	int currentWave;

public:
	Wave();

	void Increment();
	void Reset();

	int GetWave();
	int GetScaleOption(); //for the current wave
	int GetMaxAsteroidTime();
	int GetEnemyInterval();
};

