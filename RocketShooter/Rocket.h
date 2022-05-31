#pragma once
#include <SFML/Graphics.hpp>



class Rocket : public sf::Sprite   
{
	const sf::Vector2f FALL_VELOCITY;

	bool hasArmor;
	bool wasHit;

public:
	Rocket();

	sf::Vector2f GetFallVelocity();

};

