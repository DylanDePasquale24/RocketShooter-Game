#include "Game.h"

Game::Game() : HEIGHT(675), WIDTH(1200) {
	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	timeForNextAsteroid = 2000; //milliseconds
	enemyInterval = EnemyManager::GetTimeBeforeFirstEnemy(); //seconds
}

void Game::Initialize() {
	SetBackground();
	InitializeRocket();
	InitializeButtons();
	EnemyManager::InitializeEnemyTypes();
}
void Game::Update() {

	ControlRocket();   
	if (hasInteracted) {
		
		CheckIfRocketKilled();
		friendlyBullets.UpdatePositions();
		UpdateEnemy();
		UpdateAsteroids();
	}
}
void Game::Reset() {

	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	timeForNextAsteroid = 2000;  //need to change this!
	enemyInterval = EnemyManager::GetTimeBeforeFirstEnemy();
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
	Time::StartNoAsteroidClock();
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

	if (wave.GetWave() > 1) {  //only do enemies past wave 1

		if (!hasEnemy) {

			if (Time::TimeWithNoEnemy() >= enemyInterval) {  //starting interval of 5 secs (for first enemy of evry wave)
				currentEnemy = EnemyManager::CreateEnemy();
				enemyInterval = wave.GetEnemyInterval();     //changes to interval of the current wave
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
	
}
void Game::UpdateAsteroids() {

	
	if (Time::TimeWithNoAsteroid() >= timeForNextAsteroid) {
		asteroids.CreateAsteroid(wave);
		Time::StartNoAsteroidClock();

		//if you increment, then you set the time to be greater!
		timeForNextAsteroid = Random::Int(500, wave.GetMaxAsteroidTime());
	}

	asteroids.UpdatePositions();

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

	//draw asteroids
	asteroids.Draw(window);

	//draw rocket & bullets
	window.draw(rocket);  
	friendlyBullets.Draw(window);

	//draw instructions
	if (!hasInteracted) {
		sf::Sprite instructions;
		instructions.setTexture(TextureManager::GetTexture("instructions"));
		instructions.setPosition(200, 200);
		window.draw(instructions);
	}
	else {

		//draw enemy
		if (hasEnemy) {

			currentEnemy.DrawBullets(window);
			if (currentEnemy.WasHit()) {
				currentEnemy.setTexture(TextureManager::GetTexture("red" + currentEnemy.GetType()));
			}

			window.draw(currentEnemy);
		}

		//draw wave
		window.draw(wave);
	}
}



//right now you are making it so the enemies do different stuff per wave. Already have wave 1 and 2 covered. Have to make it 
//so it respawns at different times and shoots more quickly if not killed (then have them have differing healths.

//starting at wave 3, you make them shoot faster.
 

// need to make it so time before an enemy appears when every wave starts is different. 
//need to kill enemy before wave can officially end. (even if rocks end)
//also make it so you reset asteroids after gameover. and after  each wave.
//at end change timeBeforeFirstEnemy (in enemyManager) to 5 seconds. Using 2 rn so its a bit easier to work with


//have wave number affect how enemies work
//make it so the wave is timed and they increment after desginated time and have a rest period in between waves. S
//when incrementing wave, you have to rechange the enemy interval to timeBeforeFirstEnemy;
//(do incrementing last so you can hardcode each wave and see how each works individually)