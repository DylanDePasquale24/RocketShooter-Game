#include "Asteroids.h"

Asteroids::Asteroids() {
	
}
vector<Asteroid>& Asteroids::ReturnAsteroidsVec() {
	return astroidVec;
}

void Asteroids::UpdatePositions() {
	for (unsigned int i = 0; i < astroidVec.size(); i++) {

		if (astroidVec[i].IsActive()) {
			astroidVec[i].move(astroidVec[i].GetVelocity() * (Timing::GetLastFrame() / .00041f));
			astroidVec[i].rotate(.01 * (Timing::GetLastFrame() / .00041f));

			if (astroidVec[i].HitEdge()) {
				astroidVec[i].SetActiveStatus(false);   //deactivate
			}
		}
	}
}
void Asteroids::CreateAsteroid(Wave& wave) {
	
	//try repurpose
	for (unsigned int i = 0; i < astroidVec.size(); i++) {

		if (!astroidVec[i].IsActive()) { 
			astroidVec[i].Repurpose(wave.GetScaleOption());
			return;
		}
	}

	//create new if !Repurposed
	astroidVec.push_back(Asteroid(wave.GetScaleOption()));
}
void Asteroids::Draw(sf::RenderWindow& window) {

	for (unsigned int i = 0; i < astroidVec.size(); i++) {

		if (astroidVec[i].IsActive()) {
			window.draw(astroidVec[i]); 
		}
	}
}
void Asteroids::Reset() {
	astroidVec.resize(0);
}
