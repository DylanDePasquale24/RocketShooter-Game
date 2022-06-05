#include "Game.h"

Game::Game() : HEIGHT(675), WIDTH(1200) {
	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	pausedAsteroids = false;
	startedWaveBreak = false;
	timeForNextAsteroid = 2000; //milliseconds
	enemyInterval = enemyManager.GetTimeBeforeFirstEnemy(); //seconds
}

void Game::Initialize() {
	SetBackground();
	InitializeRocket();
	InitializeButtons();
	enemyManager.InitializeEnemyTypes();
}
void Game::Update() {

	ControlRocket();   
	if (hasInteracted) {
	
		CheckIfRocketKilled();
		friendlyBullets.UpdatePositions();


		UpdateAsteroids();
		UpdateEnemy();
		
		if (wave.HasEnded()) {

			if (hasEnemy) {   //stop asteroids, but need to kill enemy first
				pausedAsteroids = true;
				
			}
			else if(!hasEnemy) {

				if (!startedWaveBreak) {
					Time::StartWaveBreakClock();
					startedWaveBreak = true;
					pausedAsteroids = true;
				}
				
				//if break if over, you finally increment wave and unpause asteroids
				if (Time::SinceWaveBreak() >= wave.GetWaveBreak()) {
					IncrementWave();
					pausedAsteroids = false;
					startedWaveBreak = false;
				}
			}
		}
	}

	//after the last enemy is killed, it spawns another one for some reason. 
}
void Game::Reset() {

	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	startedWaveBreak = false;

	timeForNextAsteroid = 2000;  
	enemyInterval = enemyManager.GetTimeBeforeFirstEnemy();
	rocket.setPosition(75, HEIGHT / 2);


	enemyManager.Reset();
	wave.Reset();
	friendlyBullets.Reset(); 
	asteroids.Reset();
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
	Time::StartNoAsteroidClock();
	Time::StartWaveClock();
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

	
	if (wave.GetWave() > 1 && !startedWaveBreak) {  //only do enemies past wave 1 and dont want to update enemies on wave break

		if (!hasEnemy) {

			if (Time::WithNoEnemy() >= enemyInterval) {  //starting interval of 5 secs (for first enemy of evry wave)
				currentEnemy = enemyManager.CreateEnemy();
				enemyInterval = wave.GetEnemyInterval();     //changes to interval of the current wave
				hasEnemy = true;
				Time::StartShotFreqClock();
			}
		}
		else { //IF THERE IS AN ENEMY

			if (!currentEnemy->WasKilled()) {

				currentEnemy->UpdatePosition();

				//if wave 3 and up(), you adjust shotFrequency, so enemy shoots faster over time
				if (currentEnemy->GetShootsFaster()) {
					AdjustShotFrequency();
				}

				currentEnemy->Shoot();

				if (currentEnemy->WasDamagedBy(friendlyBullets)) {
					Time::StartWasHitClock();
					currentEnemy->SetWasHit(true);
					currentEnemy->DecrementHpBy(friendlyBullets.damage);

					if (currentEnemy->GetCurrentHealth() <= 0) {
						currentEnemy->SetWasKilled(true);
					}
				}

				if (currentEnemy->WasHit() && Time::SinceHit() >= 75) {
					currentEnemy->SetWasHit(false);
					currentEnemy->setTexture(TextureManager::GetTexture(currentEnemy->GetType()));
				}
			}
			else {
				currentEnemy->setTexture(TextureManager::GetTexture("red" + currentEnemy->GetType()));
				currentEnemy->move(-.1, .1);
				currentEnemy->rotate(.25);

				if (currentEnemy->getPosition().y >= 675 && !currentEnemy->HasActiveBullets()) {
					hasEnemy = false;
					Time::StartNoEnemyClock();
				}
			}

			currentEnemy->UpdateBullets();
		}
	}
}
void Game::AdjustShotFrequency() {
	
	if (Time::SinceLastShotFreqChange() >= enemyManager.GetShootFasterInterval(wave.GetWave())) {
		currentEnemy->IncrementShotFrequency();
		Time::StartShotFreqClock();  //bc it was just changed
	}
}
void Game::UpdateAsteroids() {

	if (!pausedAsteroids) {
		if (Time::WithNoAsteroid() >= timeForNextAsteroid) {
			asteroids.CreateAsteroid(wave);
			Time::StartNoAsteroidClock();

			//if you increment, then you set the time to be greater!
			timeForNextAsteroid = Random::Int(500, wave.GetMaxAsteroidTime());
		}
	}
	asteroids.UpdatePositions();
}
void Game::IncrementWave() {

	wave.Increment();
	Time::StartWaveClock(); 
	Time::StartNoEnemyClock();
	enemyInterval = enemyManager.GetTimeBeforeFirstEnemy();

	if (wave.GetWave() == 3) {

		enemyManager.EnemiesShootFaster(); 
	}
	else if (wave.GetWave() == 4 || wave.GetWave() == 5) {

		enemyManager.IncreaseEnemyHealths();
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

			currentEnemy->DrawBullets(window);
			if (currentEnemy->WasHit()) {
				currentEnemy->setTexture(TextureManager::GetTexture("red" + currentEnemy->GetType()));
			}

			window.draw(*currentEnemy);
		}

		//draw wave
		window.draw(wave);
	}
}





	
	//overload the IncreaseHealth function for all 3 enemy types
		//in each of these you gotta pass in the wave too (if you want it to increase differently for each wave)
		//or you could just make them increase by 2-3 shots each time  (which might as well do that)
		//then just test everything again at each wave
			//make the wave times shorter in wave class so can test easily. or just set a wave so can test it specifically


	//After this, go through entire full length game with each enemy seperately (hardcode so only get one enemy)
	//then turn and back to random and retest

	//After this, you do fullscreen, score, then allow rocket to be killed then you done


