#include "Timing.h"

//declare static variables
sf::Clock Timing::score;
sf::Clock Timing::noEnemy;
sf::Clock Timing::shotFreq;
sf::Clock Timing::noBullet;
sf::Clock Timing::wasHit;
sf::Clock Timing::noAsteroid;
sf::Clock Timing::wave;
sf::Clock Timing::waveBreak;
sf::Clock Timing::frame;
float Timing::lastFrame;




void Timing::StartScoreInterval() {
	score.restart();
}
int Timing::SinceLastScoreUpdate() {
	return score.getElapsedTime().asMilliseconds();
}

 void Timing::StartNoEnemyClock() {
	 noEnemy.restart();
 }
 int Timing::WithNoEnemy() {
	 return noEnemy.getElapsedTime().asSeconds();
 }

 void Timing::StartShotFreqClock() {
	 shotFreq.restart();
 }
 int Timing::SinceLastShotFreqChange() {
	 return shotFreq.getElapsedTime().asSeconds();
 }

 void Timing::StartNoBulletClock() {
	 noBullet.restart();
 }
 int Timing::WithNoBullet() {
	 return noBullet.getElapsedTime().asSeconds();
 }

 void Timing::StartWasHitClock() {
	wasHit.restart();
 }
 int Timing::SinceHit() {
	 return wasHit.getElapsedTime().asMilliseconds();
 }

 void Timing::StartNoAsteroidClock() {
	 noAsteroid.restart();
 }
 int Timing::WithNoAsteroid(){
	 return noAsteroid.getElapsedTime().asMilliseconds();
 }

 void Timing::StartWaveClock() {
	 wave.restart();
 }
 int Timing::OfWave() {
	 return wave.getElapsedTime().asSeconds();
 }

 void Timing::StartWaveBreakClock() {
	 waveBreak.restart();
 }
 int Timing::SinceWaveBreak() {
	 return waveBreak.getElapsedTime().asSeconds();
 }

 void Timing::StartFrame() {
	 frame.restart();
 }
 void Timing::UpdateLastFrame() {
	 lastFrame = frame.getElapsedTime().asSeconds();
 }
 float Timing::GetLastFrame() {
	 return lastFrame;
 }
 /*float Timing::FrameTime() {
	 return frame.getElapsedTime().asSeconds();
 }*/
