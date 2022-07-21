#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Random.h"
#include "TextureManager.h"
#include "Random.h"
#include "Timing.h"
#include "BulletManagers.h"
#include "Wave.h"
using std::string;
using std::vector;

class Enemy : public sf::Sprite
{

protected:
	string type;
	bool wasHit; 
	bool wasKilled; 
	bool shootsFasterOverTime;

	int totalHealth;
	int currentHealth;

	float speed;
	int maxTimeBtwnShots;
	int minTimeBtwnShots;
	int timeBtwnShots;

	int minY;
	int maxY;

	bool bulletClockStarted;

	EnemyBulletManager bullets;
	sf::Vector2f bulletVelocity;

public:

	Enemy();
 
	void DecrementHpBy(int amt);
	int GetCurrentHealth();
	int GetTotalHealth();
	void SetShootsFaster();
	bool GetShootsFaster();

	void UpdatePosition();
	void Shoot();
	void UpdateBullets();
	void DrawBullets(sf::RenderWindow& window);
	bool HasActiveBullets();
	EnemyBulletManager& ReturnBullets();

	bool WasDamagedBy(RocketBulletManager& rocketBullets);
	bool WasHit();
	bool WasKilled();
	void SetWasHit(bool val);
	void SetWasKilled(bool val);
	string GetType();


	virtual void Reset();
	virtual void Repurpose();
	virtual void IncrementShotFrequency();   //overload for each one
	virtual void IncreaseHealth(Wave& wave);
	virtual void SetShotFrequency();
};




struct Alien : public Enemy{

	Alien();
	void Reset();
	void IncrementShotFrequency();
	void IncreaseHealth(Wave& wave);

	void SetShotFrequency();

};

struct UFO : public Enemy {

	UFO();
	void Reset();
	void IncrementShotFrequency();
	void IncreaseHealth(Wave& wave);

	void SetShotFrequency();

};

struct BattleShip : public Enemy {

	BattleShip();
	void Reset();
	void IncrementShotFrequency();
	void IncreaseHealth(Wave& wave);

	void SetShotFrequency();
};
