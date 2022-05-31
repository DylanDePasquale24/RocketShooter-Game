#include "Time.h"

//declare static variables
 Timer Time::gameStart;
 Timer Time::gameEnd;
 Timer Time::noEnemyStart;
 Timer Time::noBulletStart;



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
 int Time::TimeWithNoEnemy() {

	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - noEnemyStart);
	 return duration.count();
 }

 void Time::StartNoBulletClock() {
	 noBulletStart = high_resolution_clock::now();
 }
 int Time::TimeWithNoBullet() {
	 auto currentTime = high_resolution_clock::now();
	 auto duration = duration_cast<seconds>(currentTime - noBulletStart);
	 return duration.count();
 }
