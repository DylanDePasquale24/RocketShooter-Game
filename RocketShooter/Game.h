#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "TextureManager.h"
#include "Rocket.h"
#include "Bullet.h"
#include "Button.h"

using std::vector;
using std::cout;
using std::unordered_map;


//This will Faciliate the main method 
class Game
{
	sf::Sprite background;
	const float HEIGHT = 675;
	const float WIDTH = 1200;

	Rocket rocket;
	vector<Bullet> bullets;
	unordered_map<string, Button> buttons;


	bool gameOver;
	bool hasStarted;
	bool hasInteracted;


public:

	Game();

	//main functions
	void Initialize();
	void Update();
	void Reset();
	void Draw(sf::RenderWindow& window);

	//Mutators
	void PressSpaceKey();
	void CheckButtonClicksAt(sf::Vector2f mousePos);
	void SetToInteracted();

	//Accessors
	bool GameOver();
	bool HasStarted();
	

private:
	void SetBackground();
	void InitializeRocket();
	void InitializeButtons();

	void CheckUpKeyPress();

	void CreateBullet(sf::Vector2f startPosition);
	void MoveBullets();
	void DrawBullets(sf::RenderWindow& window);
};

