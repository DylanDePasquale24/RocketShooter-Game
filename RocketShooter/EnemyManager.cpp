#include "EnemyManager.h"

vector<Enemy> EnemyManager::enemies;

void EnemyManager::InitializeEnemyTypes() {
	Enemy alien("alien", 50, .1f, 1, 5, sf::Vector2f(-.1,0));
	enemies.push_back(alien);

	Enemy ufo("ufo", 100, .05f, 3, 7, sf::Vector2f(-.065, 0));
	enemies.push_back(ufo);

	Enemy battleShip("battleship", 150, .025f, 5, 9, sf::Vector2f(-.05, 0));
	enemies.push_back(battleShip);

	for (unsigned int i = 0; i < enemies.size(); i++) {
		TextureManager::SetOriginToCenter(enemies[i]);
	}
}

Enemy EnemyManager::CreateEnemy() {
	
	
	int randomNum = Random::Int(0, 2);

	/*testing*/
	//randomNum = 2;

	enemies[randomNum].CreateInstance();
	return enemies[randomNum];
}
void EnemyManager::IncrementHealths() {

	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i].IncrementHp();
	}
}
int EnemyManager::GetEnemyInterval() {
	return ENEMY_INTERVAL;
}




