#pragma once
#include <vector>
#include <iostream>
#include <iostream>
#include <string>
#include "Bullets.h"
#include "Timing.h"
using namespace std;

class BulletManager {

protected:

	vector<Bullet*> bullets;  
	//cant create an instance of an Abstract Base Class but can still do a pointer to it
	//this way you can have the seperate bulletmanagers share a lot of functionionality except the one function you need to change with overrides

public:
	BulletManager();

	void UpdatePositions();
	void Shoot(sf::Vector2f startPosition);
	bool HasBulletAt(sf::FloatRect spriteArea);
	bool HasActiveBullet();
	void Draw(sf::RenderWindow& window);
	void Reset();

	virtual ~BulletManager() = 0;

protected:
	virtual void CreateBullet(sf::Vector2f startPosition) = 0;
	bool BulletWasRepurposed(sf::Vector2f startPosition);
};


struct RocketBulletManager : public BulletManager {
	int damage;
	RocketBulletManager();

private:
	void CreateBullet(sf::Vector2f startPosition);
};

class EnemyBulletManager : public BulletManager {

	sf::Vector2f velocity;
	string bulletType;

public:
	EnemyBulletManager();
	void Initialize(sf::Vector2f _velocity, string _bulletType);
	~EnemyBulletManager();

private:
	void CreateBullet(sf::Vector2f startPosition);
};