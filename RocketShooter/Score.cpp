#include "Score.h"

Score::Score() {
	score = 0;
	scrSprite.setTexture(TextureManager::GetTexture("score"));
	TextureManager::SetOriginToCenter(scrSprite);
	scrSprite.setPosition(75, yPos);
	maxScoreReached = false;
}

void Score::Reset() {
	score = 0;
	digitVec.resize(0);
	maxScoreReached = false;
}
void Score::Draw(sf::RenderWindow& window) {

	//draw "score:"
	window.draw(scrSprite);

	if (!maxScoreReached && score >= 10000000000000000000) {
		maxScoreReached = true;
	}

	//draw actual numbers
	if (maxScoreReached) {    
		DrawMaxScore(window);
	}
	else {
		UpdateDigits();
		DrawDigits(window);
	}
}
void Score::DrawOnEndScreen(sf::RenderWindow& window) {
	
	int newYPos = 359;

	if (maxScoreReached) {
		sf::Sprite maxScore;
		maxScore.setTexture(TextureManager::GetTexture("maxscore"));
		TextureManager::SetOriginToCenter(maxScore);
		maxScore.setPosition(407, newYPos);
		window.draw(maxScore);
	}
	else {

		int numDigits = digitVec.size();
		int numCommas = numDigits / 4;
		int counter = 0;

		int xPos = 200 + (xOffset * numDigits);

		for (int i = digitVec.size() - 1; i >= 0; i--) {

			digitVec[i].setPosition(xPos, newYPos);
			window.draw(digitVec[i]);
			xPos -= xOffset;
			counter++;

			if (counter == 3 && i != 0) {
				xPos += xOffset / 2;
				sf::Sprite comma;
				comma.setTexture(TextureManager::GetTexture("comma"));
				TextureManager::SetOriginToCenter(comma);
				comma.setPosition(xPos, newYPos + 15);
				xPos -= xOffset / 2;

				window.draw(comma);
				counter = 0;
			}
		}
	}
}

int Score::GetScoreInterval() {
	return scoreInterval;
}
void Score::IncrementDistance() {

	if (!maxScoreReached) {
		score += distanceIncrement;
	}
}
void Score::IncrementEnemy(Enemy* enemy, int wave) {

	switch (wave) {
	case 2:
		score += (unsigned long long)enemy->GetTotalHealth() * 10;
		break;
	case 3:
		score += (unsigned long long)enemy->GetTotalHealth() * 12;
		break;
	case 4:
		score += (unsigned long long)enemy->GetTotalHealth() * 15;
		break;
	case 5:
		score += (unsigned long long)enemy->GetTotalHealth() * 20;
		break;
	}
}

void Score::UpdateDigits() {

	string scoreStr = std::to_string(score);

	for (unsigned int i = 0; i < scoreStr.size(); i++) {

		string scoreDigit(1, scoreStr[i]);
		if (digitVec.size() <= i) {

			sf::Sprite newDigit;
			newDigit.setTexture(TextureManager::GetTexture(scoreDigit));
			TextureManager::SetOriginToCenter(newDigit);

			digitVec.push_back(newDigit); 
		}
		else {
			digitVec[i].setTexture(TextureManager::GetTexture(scoreDigit));
		}
	}
}
void Score::DrawDigits(sf::RenderWindow& window) {

	int numDigits = digitVec.size();
	int numCommas = numDigits / 4;   
	int counter = 0;
	
	int xPos = xPosStart + (xOffset * numDigits);  

	for (int i = digitVec.size() - 1; i >= 0; i--) {

		digitVec[i].setPosition(xPos, yPos);
		window.draw(digitVec[i]);
		xPos -= xOffset;
		counter++;

		if (counter == 3 && i != 0) {
			xPos += xOffset / 2;
			sf::Sprite comma;
			comma.setTexture(TextureManager::GetTexture("comma"));
			TextureManager::SetOriginToCenter(comma);
			comma.setPosition(xPos, yPosComma);
			xPos -= xOffset / 2;

			window.draw(comma);
			counter = 0;
		}
	}
}
void Score::DrawMaxScore(sf::RenderWindow& window) {
	sf::Sprite maxScore;
	maxScore.setTexture(TextureManager::GetTexture("maxscore"));
	TextureManager::SetOriginToCenter(maxScore);
	maxScore.setPosition(350, yPos);
	window.draw(maxScore);
}

