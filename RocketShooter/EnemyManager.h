#pragma once
#include <vector>
#include "Enemy.h"
#include "Random.h"
#include "TextureManager.h"

using std::vector;

class EnemyManager 
{
	static vector<Enemy> enemies;
	static const int timeBeforeFirstEnemy = 6;

public:

	static void InitializeEnemyTypes();
	static Enemy CreateEnemy(); 
	static void IncrementHealths(); 
	static int GetTimeBeforeFirstEnemy();
};

