#pragma once
#include <vector>
#include <iostream>
#include "Enemys.h"
#include "Random.h"
#include "TextureManager.h"
#include "Wave.h"
using std::cout;
using std::vector;

class EnemyManager 
{
	vector<Enemy*> enemies;
	const int timeBeforeFirstEnemy = 6;

	const int shootFasterIntervalW3 = 3;  //wave 3
	const int shootFasterIntervalW4 = 5;  //wave 4
	const int shootFasterIntervalW5 = 6;  //wave 5


public:

	EnemyManager();
	~EnemyManager();

	void InitializeEnemyTypes();
	Enemy* CreateEnemy(); 
	void Reset(); 

	void EnemiesShootFaster();
	void IncreaseEnemyHealths(Wave& wave);

	int GetTimeBeforeFirstEnemy();
	int GetShootFasterInterval(int wave);
};

