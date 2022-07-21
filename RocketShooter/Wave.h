#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
#include "Timing.h"
using std::string;


class Wave : public sf::Sprite
{
	int currentWave;
	const int waveBreak = 3;

public:
	Wave();

	void Increment();
	void Reset();
	void DrawOnEndScreen(sf::RenderWindow& window);

	int GetWave();
	int GetScaleOption(); //for the current wave
	int GetMaxAsteroidTime();
	int GetEnemyInterval();
	int GetWaveBreak();
	bool HasEnded();
};

