#include "Bullet.h"

Bullet::Bullet() {

}
Bullet::Bullet(sf::Vector2f startPosition) : VELOCITY(.3,0) {
	setTexture(TextureManager::GetTexture("bullet"));
	damage = 50;

	Initialize(startPosition);
}


bool Bullet::HitEdge() {
	if (this->getPosition().x > 1200) {
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
	return VELOCITY;
}