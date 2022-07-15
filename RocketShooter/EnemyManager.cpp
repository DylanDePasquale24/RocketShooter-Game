#include "EnemyManager.h"

EnemyManager::EnemyManager() {}
EnemyManager::~EnemyManager() {
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
}

void EnemyManager::InitializeEnemyTypes() {

	enemies.push_back(new Alien());
	enemies.push_back(new UFO());
	enemies.push_back(new BattleShip());

	for (unsigned int i = 0; i < enemies.size(); i++) {
		TextureManager::SetOriginToCenter(*enemies[i]);
	}
}
Enemy* EnemyManager::CreateEnemy() {
	
	int randomNum = Random::Int(0, 2);
	enemies[randomNum]->Repurpose();
	return enemies[randomNum];
}
void EnemyManager::Reset() {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->Reset();
	}
}

void EnemyManager::EnemiesShootFaster() {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->SetShootsFaster();
	}
}
void EnemyManager::IncreaseEnemyHealths(Wave& wave) {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->IncreaseHealth(wave);
	}
}

int EnemyManager::GetTimeBeforeFirstEnemy() {
	return timeBeforeFirstEnemy;
}
int EnemyManager::GetShootFasterInterval(int wave) {
	
	if (wave == 3) {
		return shootFasterIntervalW3;
	}
	else if (wave == 4) {
		return shootFasterIntervalW4;
	}
	else if (wave == 5) {
		shootFasterIntervalW5;
	}

	return 5;
}




