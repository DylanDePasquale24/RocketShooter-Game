#pragma once
#include <chrono>
using namespace std::chrono;

using Timer = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Time
{
	static Timer gameStart;
	static Timer gameEnd;

	static Timer waveStart;

	static Timer noEnemyStart;  
	static Timer noBulletStart;
	static Timer wasHitStart;
	static Timer noAsteroidStart;

public:
	
	static void StartGameClock();
	static void EndGameClock();
	static int GameRunTime();

	static void StartNoEnemyClock();
	static int TimeWithNoEnemy();

	static void StartNoBulletClock();
	static int TimeWithNoBullet();

	static void StartWasHitClock();
	static int TimeSinceHit();

	static void StartNoAsteroidClock();
	static int TimeWithNoAsteroid();

	static void StartWaveClock();
	static int TimeOfWave();

};

