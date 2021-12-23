#pragma once
#include <SFML/Graphics.hpp>



class Rocket : public sf::Sprite   //the rocket itself is the image now (can call all its functions of a sprite now)
{
	const sf::Vector2f FALL_VELOCITY;

	bool hasArmor;
	bool wasHit;

public:
	Rocket();

	sf::Vector2f GetFallVelocity();

};

