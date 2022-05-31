#include "Enemy.h"

Enemy::Enemy() {
	bullets.Initialize(sf::Vector2f(0, 0), "alienbullet");
	totalHealth = 0;
	timeBtwnShots = 5;
}
Enemy::Enemy(string _type, int _totalHealth, float _speed, int _minTimeBtwnShots, int _maxTimeBtwnShots, sf::Vector2f bulletVelocity) {
	setTexture(TextureManager::GetTexture(_type));

	bullets.Initialize(bulletVelocity, _type + "bullet"); 

	totalHealth = _totalHealth;
	hpIncrement = totalHealth;   //increments by the initial hp each time
	speed = _speed;

	maxTimeBtwnShots = _maxTimeBtwnShots;
	minTimeBtwnShots = _minTimeBtwnShots;
	timeBtwnShots = 1;  //starts off as 1

	currentHealth = 0;
}

void Enemy::CreateInstance() {
	currentHealth = totalHealth;
	bulletClockStarted = false;
	timeBtwnShots = 1;

	float xPos = 1000;
	float yPos = (float)Random::Int(minY,maxY);
	setPosition(xPos, yPos);  
}
void Enemy::IncrementHp() {
	totalHealth += hpIncrement;
}

void Enemy::UpdatePosition() {

	move(0, speed);
	if (getPosition().y >= maxY || getPosition().y <= minY) {
		speed *= -1;  //reverse direction
	}
}
void Enemy::UpdateBullets() {

	if (!bulletClockStarted) {
		Time::StartNoBulletClock();
		bulletClockStarted = true;
	}
	else if (Time::TimeWithNoBullet() >= timeBtwnShots) {  //SHOOT
		
		int width = getGlobalBounds().width;
		bullets.Shoot(sf::Vector2f(getPosition().x - width, getPosition().y));   

		//for first shot, it waits the max time and then after that, it randomizes each time
		timeBtwnShots = Random::Int(minTimeBtwnShots, maxTimeBtwnShots);

		bulletClockStarted = false;  //restarts bullet clock
	}

	bullets.UpdatePositions();
}
void Enemy::DrawBullets(sf::RenderWindow& window) {
	bullets.Draw(window);
}



