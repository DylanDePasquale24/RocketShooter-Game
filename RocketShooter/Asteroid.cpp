#include "Asteroid.h"

Asteroid::Asteroid(){}
Asteroid::Asteroid(int scaleOption) {

	scale = CalculateScale(scaleOption);
	velocity = sf::Vector2f(-.2, 0);
	isActive = true;

	setTexture(TextureManager::GetTexture("asteroid"));
	TextureManager::SetOriginToCenter(*this);
	setScale(scale * .5, scale * .5);


	setPosition(1500, Random::Int(50,625));  //fix
}
void Asteroid::Repurpose(int scaleOption) {
	scale = CalculateScale(scaleOption);
	velocity = sf::Vector2f(-.2, 0);
	isActive = true;

	setPosition(1500, Random::Int(50, 625));  //set to another random position
	setScale(scale * .5, scale * .5);
}

bool Asteroid::IsActive() {
	return isActive;
}
void Asteroid::SetActiveStatus(bool val) {
	isActive = val;
}
sf::Vector2f Asteroid::GetVelocity() {
	return velocity;
}
bool Asteroid::HitEdge() {
	if (getPosition().x < -200) {
		return true;
	}
	return false;
}


/*PRIVATE*/
int Asteroid::CalculateScale(int scaleOption) {

	switch (scaleOption) {

	case 1:
		return 1;                  //just small rocks
		break;
	case 2:
		return Random::Int(1, 2);  //small and medium rocks
		break;
	case 3:
		return Random::Int(1, 3);  //small medium and large rocks
		break;
	case 4:
		return 3;                 //just large rocks
		break;
	default:
		return -1;
	}
}
