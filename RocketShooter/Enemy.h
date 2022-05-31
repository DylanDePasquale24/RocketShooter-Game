#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Random.h"
#include "TextureManager.h"
#include "Random.h"
#include "Time.h"
#include "BulletManagers.h"
using std::string;
using std::vector;

class Enemy : public sf::Sprite
{  

	int totalHealth;   
	int currentHealth;
	int hpIncrement;

	float speed;
	int maxTimeBtwnShots;
	int minTimeBtwnShots;
	int timeBtwnShots;

	int minY = 150;
	int maxY = 500;

	bool bulletClockStarted;

	EnemyBulletManager bullets;

public:
	Enemy();
	Enemy(string _type, int _totalHealth, float _speed, int _minTimeBtwnShots, int _maxTimeBtwnShots, sf::Vector2f bulletVelocity);

	void CreateInstance();
	void IncrementHp();

	void UpdatePosition();
	void UpdateBullets();
	void DrawBullets(sf::RenderWindow& window);

	void CheckIfDamaged();

	

	
	
};


//start now by making 3 seperate classes for each alien and use inheritance 
//do it so the Enemybullet(derives from bullet) is a nested class so all derived enemies have a bullet
//or may be better to just have it so when each enemy shoots they add a bullet to one vector but each has bullet characteristics
//each should have different speeds of bullets and diff number of bullets 


//could just pass in the hpIncrement, the speed, and the total health, and the string for texture
//make it an intialize function and initialize all 3 in the EnemyManager constructor