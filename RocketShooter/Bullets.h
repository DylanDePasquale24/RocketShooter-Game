#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
using std::string;

class Bullet : public sf::Sprite
{
protected:
	sf::Vector2f velocity;
	bool isActive;

public:
	Bullet();
	Bullet(sf::Vector2f startPosition);

	bool HitEdge();
	void SetActive(bool value);
	bool IsActive();
	void Initialize(sf::Vector2f startPosition);

	sf::Vector2f GetMovementVelocity();

	virtual ~Bullet() = 0;  //so you can have Abstract Base class
};


struct RocketBullet : public Bullet {
	RocketBullet();
	RocketBullet(sf::Vector2f startPosition);
};

struct EnemyBullet : public Bullet {
	EnemyBullet();
	EnemyBullet(sf::Vector2f startPosition, sf::Vector2f _velocity, string bulletType);
};

