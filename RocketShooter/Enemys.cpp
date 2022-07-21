#include "Enemys.h"



/*==== BASE CLASS ====*/

Enemy::Enemy() {

	minY = 150;
	maxY = 500;
	totalHealth = 100;
	wasHit = false;
	wasKilled = false;
	bulletClockStarted = false;
	currentHealth = totalHealth;
	shootsFasterOverTime = false;
}

void Enemy::DecrementHpBy(int amt) {
	currentHealth -= amt;
}

int Enemy::GetCurrentHealth() {
	return currentHealth;
}
int Enemy::GetTotalHealth() {
	return totalHealth;
}
void Enemy::SetShootsFaster() {
	shootsFasterOverTime = true;
}
bool Enemy::GetShootsFaster() {
	return shootsFasterOverTime;
}

void Enemy::UpdatePosition() {

	move(0, speed * (Timing::GetLastFrame() / .00041f));
	if (getPosition().y >= maxY || getPosition().y <= minY) {
		speed *= -1;  //reverse direction
	}
}
void Enemy::Shoot() {

	if (!bulletClockStarted) {
		Timing::StartNoBulletClock();
		bulletClockStarted = true;
	}
	else if (Timing::WithNoBullet() >= timeBtwnShots) {  //SHOOT

		int width = getGlobalBounds().width;
		bullets.Shoot(sf::Vector2f(getPosition().x - width, getPosition().y));

		//for first shot, it waits the max time and then after that, it randomizes each time
		timeBtwnShots = Random::Int(minTimeBtwnShots, maxTimeBtwnShots);

		bulletClockStarted = false;  //restarts bullet clock
	}
}
void Enemy::UpdateBullets() {
	bullets.UpdatePositions();
}
void Enemy::DrawBullets(sf::RenderWindow& window) {
	bullets.Draw(window);
}
bool Enemy::HasActiveBullets() {
	return bullets.HasActiveBullet();
}
EnemyBulletManager& Enemy::ReturnBullets() {
	return bullets;
}


bool Enemy::WasDamagedBy(RocketBulletManager& rocketBullets) {

	if (rocketBullets.HasBulletAt(getGlobalBounds())) {
		return true;
	}
	return false;
}
bool Enemy::WasHit() {
	return wasHit;
}
bool Enemy::WasKilled() {
	return wasKilled;
}
void Enemy::SetWasHit(bool val) {
	wasHit = val;
}
void Enemy::SetWasKilled(bool val) {
	wasKilled = val;
}
string Enemy::GetType() {
	return type;
}

void Enemy::Reset() {
	SetShotFrequency();
	totalHealth = 50;
	shootsFasterOverTime = false;
}
void Enemy::Repurpose() {
	wasHit = false;
	wasKilled = false;
	bulletClockStarted = false;
	currentHealth = totalHealth;
	float xPos = 1000;
	float yPos = (float)Random::Int(minY, maxY);
	bullets.Reset();
	setPosition(xPos, yPos);
	setTexture(TextureManager::GetTexture(type));
	setRotation(0);
	SetShotFrequency();
}
void Enemy::IncrementShotFrequency() {

}
void Enemy::IncreaseHealth(Wave& wave) {
	totalHealth += 50;
}
void Enemy::SetShotFrequency() {
	minTimeBtwnShots = 1;
	maxTimeBtwnShots = 5;
	timeBtwnShots = 1;
}


/* ALIEN */
Alien::Alien() : Enemy() {

	type = "alien";
	speed = .1f;
	bulletVelocity = sf::Vector2f(-.1,0);
	currentHealth = totalHealth;
	Reset();


	setTexture(TextureManager::GetTexture(type));
	bullets.Initialize(bulletVelocity, type + "bullet");
}
void Alien::Reset() {

	//just the things you want to reset when start wave 1 again. Everything except the health and shooting frequency will be taken care of in repurpose
	SetShotFrequency();
	totalHealth = 50; 
	shootsFasterOverTime = false;
}
void Alien::IncrementShotFrequency() {

	if (maxTimeBtwnShots > 3) {
		maxTimeBtwnShots--;
	}
}
void Alien::IncreaseHealth(Wave& wave) {

	if (wave.GetWave() == 4) {
		totalHealth = 150;    //3 shots
	}
	else if (wave.GetWave() == 5) {
		totalHealth = 350;   //7 shots
	}
}

void Alien::SetShotFrequency() {
	minTimeBtwnShots = 1;
	maxTimeBtwnShots = 5;
	timeBtwnShots = 1;
}





/* UFO */
UFO::UFO() : Enemy() {

	type = "ufo";
	speed = .05f;
	bulletVelocity = sf::Vector2f(-.075, 0);
	currentHealth = totalHealth;
	Reset();

	setTexture(TextureManager::GetTexture(type));
	bullets.Initialize(bulletVelocity, type + "bullet");
}
void UFO::Reset() {
	totalHealth = 100;
	SetShotFrequency();
	shootsFasterOverTime = false;
}
void UFO::IncrementShotFrequency() {
	if (minTimeBtwnShots > 1) {
		minTimeBtwnShots--;
		maxTimeBtwnShots--;
		return;
	}

	if (maxTimeBtwnShots > 3) {
		maxTimeBtwnShots--;
	}
}
void UFO::IncreaseHealth(Wave& wave) {
	
	if (wave.GetWave() == 4) {
		totalHealth = 250;     //5 shots
	}
	else if (wave.GetWave() == 5) {
		totalHealth = 450;     // 9 shots
	}
}

void UFO::SetShotFrequency() {
	minTimeBtwnShots = 3;
	maxTimeBtwnShots = 7;
	timeBtwnShots = 1;
}




/* BATTLE SHIP */
BattleShip::BattleShip() : Enemy() {

	type = "battleship";
	speed = .025f;
	bulletVelocity = sf::Vector2f(-.05, 0);
	currentHealth = totalHealth;
	Reset();
	

	setTexture(TextureManager::GetTexture(type));
	bullets.Initialize(bulletVelocity, type + "bullet");
}
void BattleShip::Reset() {
	totalHealth = 150;
	SetShotFrequency();
	shootsFasterOverTime = false;
}
void BattleShip::IncrementShotFrequency() {
	
	//decrease time so eventually it goes to shooting btwn 1-4 seconds
	if (minTimeBtwnShots > 1) {
		minTimeBtwnShots--;
		maxTimeBtwnShots--;
	}
	
}
void BattleShip::IncreaseHealth(Wave& wave) {
	
	if (wave.GetWave() == 4) {
		totalHealth = 350;   //7 shots
	}
	else if (wave.GetWave() == 5) {
		totalHealth = 550;    //11 shots
	}
}

void BattleShip::SetShotFrequency() {
	minTimeBtwnShots = 5;
	maxTimeBtwnShots = 9;
	timeBtwnShots = 1;
}
