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

		//check if rocket has been shot or if alien has been shot
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

		currentEnemy.UpdatePosition();
		currentEnemy.UpdateBullets();  



















		//shoot a bullet on time interval and move their positions
		//this update bullets function is slowing the program down



		//have to check if enemy was shot and then if it passes health kill it, etc.
		//currentEnemy.CheckIfKilled(); or if shot and make rocket bullets stop if hit the alien


		//do any enemy updates (make these belong to the enemy class)
		//for was shot function pass in the bullets vector and see if any are in the same position and then if is (it counts as a shot)
		//pass in as a reference so can set the bullet as inactive if was shot

		//after a certain instance of time make it shoot  
		//(Enemy should have its own vector of bullets in it and draw those bullets and shit)
		//each shot add a bullet to the vector (have it be the same as the rocket bullets)

		//update the current enemy (movement and shots)



		//check if killed too (if killed) then 
		//hasEnemy = false;
		//start no enemy timer
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
		window.draw(currentEnemy);   
		currentEnemy.DrawBullets(window);
		//maybe take out of if statement so the bullets can continue till edge of screen, even after enemy dies
	}
}