#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "TextureManager.h"
#include "Rocket.h"
#include "Button.h"
#include "Timing.h"
#include "EnemyManager.h"
#include "BulletManagers.h"
#include "Asteroids.h"
#include "Wave.h"
#include "Score.h"
using std::vector;
using std::cout;
using std::unordered_map;


class Game
{
	sf::Sprite background;
	const float HEIGHT = 675;
	const float WIDTH = 1200;

	Rocket rocket;
	RocketBulletManager friendlyBullets;
	unordered_map<string, Button> buttons;
	Enemy* currentEnemy;
	EnemyManager enemyManager;
	Asteroids asteroids;
	Wave wave;
	Score score;
	

	bool gameOver;
	bool hasStarted;
	bool hasInteracted;
	bool onInfoScreen;
	bool hasEnemy;
	bool pausedAsteroids;
	bool startedWaveBreak;
	bool addedEnemyScore;

	int timeForNextAsteroid;
	int enemyInterval;

	const float NORMALIZE_FRAME_TIME = .00041f;
 


public:

	Game();

	
	void Initialize();
	void Update();
	void Reset();
	void Draw(sf::RenderWindow& window);

	void PressSpaceKey();
	void CheckButtonClicksAt(sf::Vector2f mousePos);
	void SetToInteracted();
	
	bool GameOver();
	bool HasStarted();
	bool HasInteracted();
	

private:
	void SetBackground();
	void InitializeRocket();
	void InitializeButtons();

	void ControlRocket();
	void CheckIfRocketKilled();

	//updates
	void UpdateEnemy();
	void AdjustShotFrequency();
	void UpdateAsteroids();
	void UpdateWave();
	void IncrementWave();
	void UpdateScore();

	void DrawHomeScreen(sf::RenderWindow& window);
	void DrawInfoScreen(sf::RenderWindow& window);
	void DrawGameOverScreen(sf::RenderWindow& window);
	void DrawGamePlay(sf::RenderWindow& window);
};

