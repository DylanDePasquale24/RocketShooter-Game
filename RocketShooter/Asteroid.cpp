#include "Asteroid.h"

Asteroid::Asteroid(){}
Asteroid::Asteroid(int scaleOption) {
	
	setRadius(83);
	setPointCount(10);
	scale = CalculateScale(scaleOption);
	velocity = sf::Vector2f(-.2, 0);
	isActive = true;

	setTexture(TextureManager::GetTexturePtr("asteroid"));
	setOrigin(getRadius(),getRadius());


	setScale(scale * .5, scale * .5);
	setPosition(1500, Random::Int(50,625));  
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
		return 2;
	}
}


//to check if its being hit, see if the rocket intersects with any point that is from the origin and the radius of the circle, 
//but be careful of the scale