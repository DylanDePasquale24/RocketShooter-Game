#pragma once
#include <SFML/Graphics.hpp>


class Timing
{
	static sf::Clock score;

	static sf::Clock wave;
	static sf::Clock waveBreak;

	static sf::Clock noEnemy;
	static sf::Clock shotFreq;
	static sf::Clock noBullet;
	static sf::Clock wasHit;
	static sf::Clock noAsteroid;

	static sf::Clock frame;
	static float lastFrame;

public:
	static void StartScoreInterval();
	static int SinceLastScoreUpdate();

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

	static void StartFrame();
	static void UpdateLastFrame();
	static float GetLastFrame();
	/*static float FrameTime();*/
};

