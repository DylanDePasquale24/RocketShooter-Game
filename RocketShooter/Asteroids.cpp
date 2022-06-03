#include "Asteroids.h"

Asteroids::Asteroids() {
	
}

void Asteroids::UpdatePositions() {
	for (unsigned int i = 0; i < astroidVec.size(); i++) {

		if (astroidVec[i].IsActive()) {
			astroidVec[i].move(astroidVec[i].GetVelocity());
			astroidVec[i].rotate(.01);

			if (astroidVec[i].HitEdge()) {
				astroidVec[i].SetActiveStatus(false);   //deactivate
			}
		}
	}
}
void Asteroids::CreateAsteroid(Wave& wave) {


	//the wave is for the size
	
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
