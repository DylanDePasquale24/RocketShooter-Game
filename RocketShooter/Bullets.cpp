#include "Bullets.h"


/*Bullet */
Bullet::Bullet() {
	isActive = true;
}
Bullet::Bullet(sf::Vector2f startPosition) {
	Initialize(startPosition);
}

bool Bullet::HitEdge() {
	if (this->getPosition().x > 1200 || this->getPosition().x < 0) {
		return true;
	}
	return false;
}
void Bullet::SetActive(bool value) {
	isActive = value;
}
bool Bullet::IsActive() {
	return isActive;
}
void Bullet::Initialize(sf::Vector2f startPosition) {
	isActive = true;
	setPosition(startPosition);
}


sf::Vector2f Bullet::GetMovementVelocity() {
	return velocity;
}
Bullet::~Bullet() {}



/*RocketBullet*/
RocketBullet::RocketBullet() : Bullet(){}
RocketBullet::RocketBullet(sf::Vector2f startPosition) : Bullet(startPosition){
	velocity = sf::Vector2f(.3, 0);
	setTexture(TextureManager::GetTexture("bullet"));
}



/*EnemyBullet*/
EnemyBullet::EnemyBullet() {}
EnemyBullet::EnemyBullet(sf::Vector2f startPosition, sf::Vector2f _velocity, string bulletType) : Bullet(startPosition) {
	velocity = _velocity;
	setTexture(TextureManager::GetTexture(bulletType));
}