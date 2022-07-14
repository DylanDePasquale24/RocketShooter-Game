#include "Rocket.h"

Rocket::Rocket() : FALL_VELOCITY(0,.2) {}

bool Rocket::WasHitBy(EnemyBulletManager& enemyBullets) {
	if (enemyBullets.HasBulletAt(getGlobalBounds())) {
		return true;
	}
	return false;
}
bool Rocket::WasHitBy(vector<Asteroid>& asteroids) {
	//iterate through all the asteroids and see if they intersect with rocket

	for (unsigned int i = 0; i < asteroids.size(); i++) {
		if (asteroids[i].IsActive() && asteroids[i].getGlobalBounds().intersects(getGlobalBounds())) {
			return true;
		}
	}
	return false;
}
sf::Vector2f Rocket::GetFallVelocity() {
	return FALL_VELOCITY;
}
