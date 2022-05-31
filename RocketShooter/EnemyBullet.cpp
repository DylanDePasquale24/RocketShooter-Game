#include "EnemyBullet.h"

EnemyBullet::EnemyBullet() :Bullet() {

}
EnemyBullet::EnemyBullet(sf::Vector2f startPosition) : Bullet(startPosition) {

	setTexture(TextureManager::GetTexture("alienbullet"));   //just change the texture
	//need to change the velocity too
}

//make bullet an abstract base class and then make rocketBullet and enemy bullet classes
//do this all in one bullet file just have multiple classes in one file
//maybe in each alien constructor you change the bullet characteristics too?
//make so each enemy has a different texture for the bullet and a diff bullet speed. 