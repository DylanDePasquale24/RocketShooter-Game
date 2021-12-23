#include "Rocket.h"

Rocket::Rocket() : FALL_VELOCITY(0,.2) { //y gets greater as you go down
	hasArmor = false;
	wasHit = false;
}

sf::Vector2f Rocket::GetFallVelocity() {
	return FALL_VELOCITY;
}
