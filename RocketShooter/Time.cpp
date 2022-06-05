#include "Time.h"

//declare static variables
 Timer Time::gameStart;
 Timer Time::gameEnd;
 Timer Time::noEnemyStart;
 Timer Time::shotFreqStart;
 Timer Time::noBulletStart;
 Timer Time::wasHitStart;
 Timer Time::noAsteroidStart;
 Timer Time::waveStart;
 Timer Time::waveBreakStart;


 void Time::StartGameClock() {
	 gameStart = high_resolution_clock::now();
 }
 void Time::EndGameClock() {
	 gameEnd = high_resolution_clock::now();
 }
 int Time::GameRunTime() {

	 auto duration = duration_cast<seconds>(gameEnd - gameStart);
	 return duration.count();
 }

 void Time::StartNoEnemyClock() {
	 noEnemyStart = high_resolution_clock::now();
 }
 int Time::WithNoEnemy() {

	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - noEnemyStart);
	 return duration.count();
 }

 void Time::StartShotFreqClock() {
	 shotFreqStart = high_resolution_clock::now();
 }
 int Time::SinceLastShotFreqChange() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - shotFreqStart);
	 return duration.count();
 }

 void Time::StartNoBulletClock() {
	 noBulletStart = high_resolution_clock::now();
 }
 int Time::WithNoBullet() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - noBulletStart);
	 return duration.count();
 }

 void Time::StartWasHitClock() {
	wasHitStart = high_resolution_clock::now();
 }
 int Time::SinceHit() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<milliseconds>(currentTime - wasHitStart);
	 return duration.count();
 }

 void Time::StartNoAsteroidClock() {
	 noAsteroidStart = high_resolution_clock::now();
 }
 int Time::WithNoAsteroid(){
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<milliseconds>(currentTime - noAsteroidStart);
	 return duration.count(); //milliseconds
 }

 void Time::StartWaveClock() {
	 waveStart = high_resolution_clock::now();
 }
 int Time::OfWave() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - waveStart);
	 return duration.count();
 }

 void Time::StartWaveBreakClock() {
	 waveBreakStart = high_resolution_clock::now();
 }
 int Time::SinceWaveBreak() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - waveBreakStart);
	 return duration.count();
 }
