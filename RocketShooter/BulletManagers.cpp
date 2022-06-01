#include "BulletManagers.h"

/*Bullet Manager*/
BulletManager::BulletManager() {}
BulletManager::~BulletManager() {}

void BulletManager::UpdatePositions() {
	for (unsigned int i = 0; i < bullets.size(); i++) {

		Bullet* currentBullet = bullets[i];

		if (currentBullet->IsActive()) {
			currentBullet->move(currentBullet->GetMovementVelocity());

			if (currentBullet->HitEdge()) {
				currentBullet->SetActive(false);
			}
		}
	}
}
void BulletManager::Shoot(sf::Vector2f startPosition) {

	//if dont repurpose a bullet then create a new one
	if (!BulletWasRepurposed(startPosition)) {
 		CreateBullet(startPosition);
	}
}
bool BulletManager::HasBulletAt(sf::FloatRect spriteArea) {

	for (unsigned int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->IsActive() && bullets[i]->getGlobalBounds().intersects(spriteArea)) {

			bullets[i]->SetActive(false);  //unactivate bullet
			return true;
		}
	}
	return false;

}
bool BulletManager::HasActiveBullet() {
	for (unsigned int i = 0; i < bullets.size(); i++) {
		if (bullets[i]->IsActive()) {
			return true;
		}
	}
	return false;
}
void BulletManager::Draw(sf::RenderWindow& window) {
	for (unsigned int i = 0; i < bullets.size(); i++) {

		//only draw active bullets
		if (bullets[i]->IsActive()) {
			window.draw(*bullets[i]);
		}
	}
}
void BulletManager::Reset() {
	for (int i = 0; i < bullets.size(); i++) {
		delete bullets[i];
	}
	bullets.resize(0);
}

bool BulletManager::BulletWasRepurposed(sf::Vector2f startPosition) {
	for (unsigned int i = 0; i < bullets.size(); i++) {

		//if there is an inactive one, use that 
		if (!bullets[i]->IsActive()) {
			bullets[i]->Initialize(startPosition);
			return true;
		}
	}

	return false;
}


/*Rocket Bullet Manager*/
RocketBulletManager::RocketBulletManager() : BulletManager() {
	damage = 50;
}
void RocketBulletManager::CreateBullet(sf::Vector2f startPosition) {
	bullets.push_back(new RocketBullet(startPosition));
}

/*Enemy Bullet Manager*/
EnemyBulletManager::EnemyBulletManager() : BulletManager() {}
void EnemyBulletManager::Initialize(sf::Vector2f _velocity, string _bulletType) {
	velocity = _velocity;
	bulletType = _bulletType;
};
void EnemyBulletManager::CreateBullet(sf::Vector2f startPosition) {

	bullets.push_back(new EnemyBullet(startPosition, velocity, bulletType));
}