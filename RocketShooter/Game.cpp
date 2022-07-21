#include "Game.h"

Game::Game() : HEIGHT(675), WIDTH(1200) {
	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	onInfoScreen = false;
	hasEnemy = false;
	pausedAsteroids = false;
	startedWaveBreak = false;
	addedEnemyScore = false;
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
		UpdateWave();
		UpdateScore();	
	}
}
void Game::Reset() {

	gameOver = false;
	hasStarted = false;
	hasInteracted = false;
	hasEnemy = false;
	startedWaveBreak = false;
	addedEnemyScore = false;

	timeForNextAsteroid = 2000;  
	enemyInterval = enemyManager.GetTimeBeforeFirstEnemy();
	rocket.setPosition(75, HEIGHT / 2);


	enemyManager.Reset();
	wave.Reset();
	score.Reset();
	friendlyBullets.Reset(); 
	asteroids.Reset();
}
void Game::Draw(sf::RenderWindow& window) {

	if (!hasStarted) { 

		if (onInfoScreen) {
			DrawInfoScreen(window);
		}
		else {
			DrawHomeScreen(window);
		}
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
	if (buttons["start"].WasClickedAt(mousePos) && !onInfoScreen) {
		buttons["start"].OnClick();
	}

	//info
	if (buttons["info"].WasClickedAt(mousePos)) {
		buttons["info"].OnClick();
	}

	//continue
	if (buttons["continue"].WasClickedAt(mousePos)) {
		buttons["continue"].OnClick();
	}

	//back
	if (buttons["back"].WasClickedAt(mousePos)) {
		buttons["back"].OnClick();
	}
}
void Game::SetToInteracted() {
	hasInteracted = true;
	Timing::StartScoreInterval();
	Timing::StartNoAsteroidClock();
	Timing::StartWaveClock();
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

	buttons.emplace("start", Button(sf::Vector2f(543, 500), "start", [this]() {

		hasStarted = true;
	}));
	buttons.emplace("info", Button(sf::Vector2f(680, 508), "info", [this]() {

		onInfoScreen = true;
	}));
	buttons.emplace("continue", Button(sf::Vector2f(475, 575), "continue", [this]() {
		
		Reset();
	}));
	buttons.emplace("back", Button(sf::Vector2f(543, 595), "back", [this]() {
		onInfoScreen = false;
	}));
}

void Game::ControlRocket() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		rocket.move(-rocket.GetFallVelocity() * (Timing::GetLastFrame() / NORMALIZE_FRAME_TIME));
		
		//upon first movement
		if (hasInteracted == false) {
			SetToInteracted();
		}

	}
	else if(hasInteracted) {

		rocket.move(rocket.GetFallVelocity() * (Timing::GetLastFrame() / NORMALIZE_FRAME_TIME));
	}
}
void Game::CheckIfRocketKilled() {

	//hit edge
	if (rocket.getPosition().y < 0 || rocket.getPosition().y > HEIGHT) {
		gameOver = true;
	}

	//hit by enemy bullet
	if (hasEnemy && rocket.WasHitBy(currentEnemy->ReturnBullets())) {
		gameOver = true;
	}

	//hit by asteroid
	if (rocket.WasHitBy(asteroids.ReturnAsteroidsVec())) {
		gameOver = true;
	}
}

void Game::UpdateEnemy() {

	
	if (wave.GetWave() > 1 && !startedWaveBreak) {  //only do enemies past wave 1 and dont want to update enemies on wave break

		if (!hasEnemy) {

			if (Timing::WithNoEnemy() >= enemyInterval) {  //starting interval of 5 secs (for first enemy of evry wave)
				currentEnemy = enemyManager.CreateEnemy();
				enemyInterval = wave.GetEnemyInterval();     //changes to interval of the current wave
				hasEnemy = true;
				Timing::StartShotFreqClock();
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
					Timing::StartWasHitClock();
					currentEnemy->SetWasHit(true);
					currentEnemy->DecrementHpBy(friendlyBullets.damage);

					if (currentEnemy->GetCurrentHealth() <= 0) {
						currentEnemy->SetWasKilled(true);
					}
				}

				if (currentEnemy->WasHit() && Timing::SinceHit() >= 75) {
					currentEnemy->SetWasHit(false);
					currentEnemy->setTexture(TextureManager::GetTexture(currentEnemy->GetType()));
				}
			}
			else { //enemy was killed

				//update score (only once)
				if (!addedEnemyScore) {
					score.IncrementEnemy(currentEnemy, wave.GetWave());
					addedEnemyScore = true;
				}
		

				currentEnemy->setTexture(TextureManager::GetTexture("red" + currentEnemy->GetType()));
				currentEnemy->move(-.1, .1);
				currentEnemy->rotate(.25);

				if (currentEnemy->getPosition().y >= 675 && !currentEnemy->HasActiveBullets()) {
					hasEnemy = false;
					addedEnemyScore = false;
					Timing::StartNoEnemyClock();
				}
			}

			currentEnemy->UpdateBullets();
		}
	}


	//score increment for enemies should be in the thousands. health times 10.
}
void Game::AdjustShotFrequency() {
	
	if (Timing::SinceLastShotFreqChange() >= enemyManager.GetShootFasterInterval(wave.GetWave())) {
		currentEnemy->IncrementShotFrequency();
		Timing::StartShotFreqClock();  //bc it was just changed
	}
}
void Game::UpdateAsteroids() {

	if (!pausedAsteroids) {
		if (Timing::WithNoAsteroid() >= timeForNextAsteroid) {
			asteroids.CreateAsteroid(wave);
			Timing::StartNoAsteroidClock();

			//if you increment, then you set the time to be greater!
			timeForNextAsteroid = Random::Int(500, wave.GetMaxAsteroidTime());
		}
	}
	asteroids.UpdatePositions();
}
void Game::UpdateWave() {
	if (wave.HasEnded()) {

		if (hasEnemy) {   //stop asteroids, but need to kill enemy first
			pausedAsteroids = true;

		}
		else if (!hasEnemy) {

			if (!startedWaveBreak) {
				Timing::StartWaveBreakClock();
				startedWaveBreak = true;
				pausedAsteroids = true;
			}

			//if break if over, you finally increment wave and unpause asteroids
			if (Timing::SinceWaveBreak() >= wave.GetWaveBreak()) {
				IncrementWave();
				pausedAsteroids = false;
				startedWaveBreak = false;
			}
		}
	}
}
void Game::IncrementWave() {

	wave.Increment();
	Timing::StartWaveClock(); 
	Timing::StartNoEnemyClock();
	enemyInterval = enemyManager.GetTimeBeforeFirstEnemy();

	if (wave.GetWave() == 3) {

		enemyManager.EnemiesShootFaster(); 
	}
	else if (wave.GetWave() == 4 || wave.GetWave() == 5) {

		enemyManager.IncreaseEnemyHealths(wave);
	}
}
void Game::UpdateScore() {

	if (!gameOver) {   
		if (Timing::SinceLastScoreUpdate() >= score.GetScoreInterval()) {
			score.IncrementDistance();
			Timing::StartScoreInterval();
		}
	}

	//make sure it doesn't increment during the wave break or when wave has ended and waiting for enemy to die
	//and update for every enemy that dies (do this in update enemy)
}

void Game::DrawHomeScreen(sf::RenderWindow& window){
	sf::Sprite homeScreen;
	homeScreen.setTexture(TextureManager::GetTexture("homescreen"));
	window.draw(homeScreen);

	window.draw(buttons["start"]);
	window.draw(buttons["info"]);
}
void Game::DrawInfoScreen(sf::RenderWindow& window) {

	//draw space background
	sf::Sprite newBackground; 
	newBackground.setTexture(TextureManager::GetTexture("black"));
	window.draw(newBackground);


	//draw text
	sf::Sprite text;
	text.setTexture(TextureManager::GetTexture("infotxt"));
	window.draw(text);

	//draw back button
	window.draw(buttons["back"]);
}
void Game::DrawGameOverScreen(sf::RenderWindow& window) {

	sf::Sprite gameOverScreen;
	gameOverScreen.setTexture(TextureManager::GetTexture("gameoverscreen"));
	window.draw(gameOverScreen);

	score.DrawOnEndScreen(window);
	wave.DrawOnEndScreen(window);
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

		//draw score
		score.Draw(window);
	}
}



