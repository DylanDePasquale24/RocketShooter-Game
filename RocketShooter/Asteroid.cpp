#include "Asteroid.h"

Asteroid::Asteroid(){}
Asteroid::Asteroid(int scaleOption) {
	
	setRadius(77);
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

bool Asteroid::ContainsRocketRect(sf::FloatRect rect) {

	//check all 4 corners of rectangle and see if the circle contains any of those points

	sf::Vector2f topLeft(rect.left, rect.top);
	sf::Vector2f topRight(rect.left + rect.width, rect.top);
	sf::Vector2f bottomLeft(rect.left, rect.top + rect.height);
	sf::Vector2f bottomRight(rect.left + rect.width, rect.top + rect.height);

	return ContainsPoint(topLeft) || ContainsPoint(topRight) || ContainsPoint(bottomLeft) || ContainsPoint(bottomRight);
}



/*PRIVATE*/
bool Asteroid::ContainsPoint(sf::Vector2f point) {

	sf::Vector2f center = getPosition();
	float x = point.x - center.x;
	float y = point.y - center.y;

	x *= x;
	y *= y;

	float curRadius = getRadius() * scale * 0.5;

	float r = curRadius * curRadius;
	return ((x + y) < r);
}
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
