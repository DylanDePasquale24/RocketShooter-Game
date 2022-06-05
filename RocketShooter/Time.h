#pragma once
#include <chrono>
using namespace std::chrono;

using Timer = std::chrono::time_point<std::chrono::high_resolution_clock>;

class Time
{
	static Timer gameStart;
	static Timer gameEnd;

	static Timer waveStart;
	static Timer waveBreakStart;

	static Timer noEnemyStart;  
	static Timer shotFreqStart;
	static Timer noBulletStart;
	static Timer wasHitStart;
	static Timer noAsteroidStart;

public:
	
	static void StartGameClock();
	static void EndGameClock();
	static int GameRunTime();

	static void StartNoEnemyClock();
	static int WithNoEnemy();

	static void StartShotFreqClock();
	static int SinceLastShotFreqChange();

	static void StartNoBulletClock();
	static int WithNoBullet();

	static void StartWasHitClock();
	static int SinceHit();

	static void StartNoAsteroidClock();
	static int WithNoAsteroid();

	static void StartWaveClock();
	static int OfWave();

	static void StartWaveBreakClock();
	static int SinceWaveBreak();

};

