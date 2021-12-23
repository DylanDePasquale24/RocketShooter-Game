#include "Game.h"

Game::Game() : HEIGHT(675), WIDTH(1200) {
	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
}

void Game::Initialize() {
	SetBackground();
	InitializeRocket();
	InitializeButtons();
}
void Game::Update() {

	
	CheckUpKeyPress();
	MoveBullets();
	
}
void Game::Reset() {

	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	rocket.setPosition(75, HEIGHT / 2);

	bullets.resize(0); 
}
void Game::Draw(sf::RenderWindow& window) {

	if (!hasStarted) {  //HOME SCREEN

		sf::Sprite homeScreen;
		homeScreen.setTexture(TextureManager::GetTexture("homescreen"));
		window.draw(homeScreen);

		window.draw(buttons["start"]);
		window.draw(buttons["stats"]);
	}
	else if (gameOver) {  //GAME OVER SCREEN

		sf::Sprite gameOverScreen;
		gameOverScreen.setTexture(TextureManager::GetTexture("gameoverscreen"));
		window.draw(gameOverScreen);

		window.draw(buttons["continue"]);

	}
	else {  //PLAY GAME

		window.draw(background);
		window.draw(rocket);  //can just draw the rocket object bc its a sprite
		DrawBullets(window);

		if (!hasInteracted) {
			sf::Sprite instructions;
			instructions.setTexture(TextureManager::GetTexture("instructions"));
			instructions.setPosition(200, 200);
			window.draw(instructions);
		}
	}

}

void Game::PressSpaceKey() {

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {

	float startX = rocket.getLocalBounds().width / 2 + 75;
	float startY = rocket.getPosition().y;

	CreateBullet(sf::Vector2f(startX, startY));
	//}
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
}

bool Game::GameOver() {
	return gameOver;
}
bool Game::HasStarted() {
	return hasStarted;
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

void Game::CheckUpKeyPress() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		hasInteracted = true;

		rocket.move(-rocket.GetFallVelocity());

		if (rocket.getPosition().y < 0) {
			gameOver = true;
		}
	}
	else if(hasInteracted) {

		rocket.move(rocket.GetFallVelocity());

		if (rocket.getPosition().y > HEIGHT) {
			gameOver = true;
		}
	}
}

void Game::CreateBullet(sf::Vector2f startPosition) {

	//Go through vector and try to repurpose a bullet first
	bool bulletReused = false;
	for (int i = 0; i < bullets.size(); i++) {

		//if there is an inactive one, use that 
		if (!bullets[i].IsActive()) {
			bullets[i].Initialize(startPosition);
			bulletReused = true;
			break;
		}
	}

	//if a bullet wasn't repurposed, then you create a new one
	if (!bulletReused) {
		Bullet newBullet(startPosition);
		bullets.push_back(newBullet);
	}
}
void Game::MoveBullets() {
	for (int i = 0; i < bullets.size(); i++) {

		Bullet& currentBullet = bullets[i];

		if (currentBullet.IsActive()) {
			currentBullet.move(currentBullet.GetMovementVelocity());
		}

		if (currentBullet.HitEdge()) {
			currentBullet.SetActive(false);
		}

	}
}
void Game::DrawBullets(sf::RenderWindow& window) {
	for (int i = 0; i < bullets.size(); i++) {

		//only draw active bullets
		if (bullets[i].IsActive()) {
			window.draw(bullets[i]);
		}
	}
}