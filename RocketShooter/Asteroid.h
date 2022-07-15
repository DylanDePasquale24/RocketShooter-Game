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

	bool ContainsRocketRect(sf::FloatRect rect);

private:

	bool ContainsPoint(sf::Vector2f point);
	int CalculateScale(int scaleOption);
};
