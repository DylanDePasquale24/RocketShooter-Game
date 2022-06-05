#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Random.h"

class Asteroid : public sf::Sprite
{
	sf::Vector2f velocity;
	float scale;
	bool isActive;
	
public:

	Asteroid();
	Asteroid(int scaleOption);
	void Repurpose(int scaleOption);

	bool IsActive();
	void SetActiveStatus(bool val);
	sf::Vector2f GetVelocity();
	bool HitEdge();

private:
	int CalculateScale(int scaleOption);
	
};

