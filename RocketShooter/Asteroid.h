#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Random.h"

class Asteroid : public sf::CircleShape
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

//will need to change the asteroid constructor and repurpose functions
//bc now dealing with a shape and not a sprite
