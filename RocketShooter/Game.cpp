#include "Game.h"

Game::Game() : HEIGHT(675), WIDTH(1200) {
	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
}

void Game::Initialize() {
	SetBackground();
	InitializeRocket();
	InitializeButtons();
	EnemyManager::InitializeEnemyTypes();
}
void Game::Update() {

	ControlRocket();   
	//if you shoot it resets the noenemy timer so if you keep shooting no enemy appears

	if (hasInteracted) {
		
		CheckIfRocketKilled();
		//also in this function check if was shot by the alien too (pass in enemy bullet vector?)

		friendlyBullets.UpdatePositions();


		UpdateEnemy();
	}
}
void Game::Reset() {

	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	rocket.setPosition(75, HEIGHT / 2);

	friendlyBullets.Reset(); 
}
void Game::Draw(sf::RenderWindow& window) {

	if (!hasStarted) { 
		DrawHomeScreen(window);
	}
	else if (gameOver) {  
		DrawGameOverScreen(window);
	}
	else {  
		DrawGamePlay(window);
	}
}

void Game::PressSpaceKey() {
	float startX = rocket.getLocalBounds().width / 2 + 75;
	float startY = rocket.getPosition().y;

	friendlyBullets.Shoot(sf::Vector2f(startX, startY));
}
void Game::CheckButtonClicksAt(sf::Vector2f mousePos) {

	//start
	if (buttons["start"].WasClickedAt(mousePos)) {
		buttons["start"].OnClick();
	}

	//stats
	if (buttons["stats"].WasClickedAt(mousePos)) {
		buttons["stats"].OnClick();
	}

	//continue
	if (buttons["continue"].WasClickedAt(mousePos)) {
		buttons["continue"].OnClick();
	}
}
void Game::SetToInteracted() {
	hasInteracted = true;
	Time::StartGameClock();
	Time::StartNoEnemyClock();
}

bool Game::GameOver() {
	return gameOver;
}
bool Game::HasStarted() {
	return hasStarted;
}
bool Game::HasInteracted() {
	return hasInteracted;
}



/*PRIVATE*/
void Game::SetBackground() {

	//position is just going to be 0,0
	background.setTexture(TextureManager::GetTexture("space"));
}
void Game::InitializeRocket() {

	rocket.setTexture(TextureManager::GetTexture("rocket"));
	TextureManager::SetOriginToCenter(rocket);
	rocket.setPosition(75, HEIGHT / 2);
}
void Game::InitializeButtons() {

	buttons.emplace("start", Button(sf::Vector2f(430, 500), "start", [this]() {

		hasStarted = true;
	}));
	buttons.emplace("stats", Button(sf::Vector2f(630, 500), "stats", [this]() {

		//do functionality
	}));
	buttons.emplace("continue", Button(sf::Vector2f(475, 575), "continue", [this]() {
		
		Reset();
	}));
}

void Game::ControlRocket() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		rocket.move(-rocket.GetFallVelocity());

		//upon first movement
		if (hasInteracted == false) {
			SetToInteracted();
		}

	}
	else if(hasInteracted) {

		rocket.move(rocket.GetFallVelocity());
	}
}
void Game::CheckIfRocketKilled() {
	if (rocket.getPosition().y < 0 || rocket.getPosition().y > HEIGHT) {
		gameOver = true;
		Time::EndGameClock();
	}
}

void Game::UpdateEnemy() {

	if (!hasEnemy) {

		if (Time::TimeWithNoEnemy() >= EnemyManager::GetEnemyInterval()) {
			currentEnemy = EnemyManager::CreateEnemy();
			hasEnemy = true;
		}
	}
	else { //IF THERE IS AN ENEMY

		if (!currentEnemy.WasKilled()) {

			currentEnemy.UpdatePosition();
			currentEnemy.Shoot();

			if (currentEnemy.WasDamagedBy(friendlyBullets)) {
				Time::StartWasHitClock();
				currentEnemy.SetWasHit(true);
				currentEnemy.DecrementHpBy(friendlyBullets.damage);

				if (currentEnemy.GetCurrentHealth() <= 0) {
					currentEnemy.SetWasKilled(true);
				}
			}

			if (currentEnemy.WasHit() && Time::TimeSinceHit() >= 75) {
				currentEnemy.SetWasHit(false);
				currentEnemy.setTexture(TextureManager::GetTexture(currentEnemy.GetType()));
			}
		}
		else {
			currentEnemy.setTexture(TextureManager::GetTexture("red" + currentEnemy.GetType()));
			currentEnemy.move(-.1, .1); 
			currentEnemy.rotate(.25);
			
			if (currentEnemy.getPosition().y >= 675 && !currentEnemy.HasActiveBullets()) {
				hasEnemy = false;
				Time::StartNoEnemyClock();
			}
		}

		currentEnemy.UpdateBullets(); 
	}
}

void Game::DrawHomeScreen(sf::RenderWindow& window){
	sf::Sprite homeScreen;
	homeScreen.setTexture(TextureManager::GetTexture("homescreen"));
	window.draw(homeScreen);

	window.draw(buttons["start"]);
	window.draw(buttons["stats"]);
}
void Game::DrawGameOverScreen(sf::RenderWindow& window) {
	sf::Sprite gameOverScreen;
	gameOverScreen.setTexture(TextureManager::GetTexture("gameoverscreen"));
	window.draw(gameOverScreen);

	window.draw(buttons["continue"]);
}
void Game::DrawGamePlay(sf::RenderWindow& window) {
	window.draw(background);
	window.draw(rocket);  //can just draw the rocket object bc its a sprite
	friendlyBullets.Draw(window);

	//draw instructions
	if (!hasInteracted) {
		sf::Sprite instructions;
		instructions.setTexture(TextureManager::GetTexture("instructions"));
		instructions.setPosition(200, 200);
		window.draw(instructions);
	}

	//draw the enemy
	if (hasEnemy) {

		currentEnemy.DrawBullets(window);
		if (currentEnemy.WasHit()) {
			currentEnemy.setTexture(TextureManager::GetTexture("red" + currentEnemy.GetType()));
		}

		window.draw(currentEnemy);
	}
}