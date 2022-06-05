#include "Wave.h"

Wave::Wave() {

	currentWave = 1;   //currently changing for tests (need it to be 1)

	setTexture(TextureManager::GetTexture("wave1"));
	TextureManager::SetOriginToCenter(*this);
	setPosition(600, 50);
}

void Wave::Increment() {
	currentWave++;

	string image = "wave";
	image = image + std::to_string(currentWave);

	setTexture(TextureManager::GetTexture(image));
}
void Wave::Reset() {
	currentWave = 1;
	setTexture(TextureManager::GetTexture("wave1"));
}

int Wave::GetWave() {
	return currentWave;
}
int Wave::GetScaleOption() {

	//small = 1
	//med = 2
	//large = 3

	if (currentWave == 1) {  //can only do small rocks 
		return 1;
	}
	else if (currentWave == 2) {  //small and medium
		return 2;
	}
	else if (currentWave == 3 || currentWave == 4) {  //small medium and large
		return 3;
	}
	else if (currentWave == 5) {  //only large
		return 4;
	}
	else {
		return -1;
	}
}
int Wave::GetMaxAsteroidTime() {

	//these times are in milliseconds!!!

	if (currentWave == 1) {
		return 2000;
	}
	else if (currentWave == 2) {
		return 1500;
	}
	else if (currentWave == 3) {
		return 1000;
	}
	else if (currentWave == 4) {
		return 500;
	}
	else {
		return 750;
	}
}
int Wave::GetEnemyInterval() {

	//each recurring enemy should take 
		//wave 2 & 3= 3 seconds
		//w4 = 8s
		//w5 = 15s

	switch (currentWave) {
		
		//2 and 3 should be 3 seconds
	case 2:
		return 3;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 8;
		break;
	case 5:
		return 15;
		break;
	default:
		return 10;
	}
}
int Wave::GetWaveBreak() {
	return waveBreak;
}
bool Wave::HasEnded() {

	if (currentWave == 1) {
		if (Time::OfWave() >= 30) {  
			return true;
		}
	}
	else if (currentWave == 2) {
		if (Time::OfWave() >= 50) {   
			return true;
		}
	}
	else if(currentWave == 3 || currentWave == 4) {

		if (Time::OfWave() >= 80) {   
			return true;
		}
	}

	return false;
}
