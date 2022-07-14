#pragma once
#include <SFML/Graphics.hpp>
#include "BulletManagers.h"
#include "Asteroid.h"



class Rocket : public sf::Sprite   
{
	const sf::Vector2f FALL_VELOCITY;

public:

	Rocket();
	bool WasHitBy(EnemyBulletManager& enemyBullets);
	bool WasHitBy(vector<Asteroid>& asteroids);
	sf::Vector2f GetFallVelocity();

};

