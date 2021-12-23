#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Bullet : public sf::Sprite
{
	int damage;
	const sf::Vector2f VELOCITY;
	bool isActive;

public:
	Bullet();
	Bullet(sf::Vector2f startPosition);

	bool HitEdge();
	void SetActive(bool value);
	bool IsActive();
	void Initialize(sf::Vector2f startPosition);

	sf::Vector2f GetMovementVelocity();

};

