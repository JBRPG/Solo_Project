#include "bullet.hpp"

void Bullet::collideWith(Player*){
	if (!enemyShot) return;

	// destroy the bullet
	// player health reduction taken care of
	// in Player's code
	myScene->storeRemovedEntity(this);


}

void Bullet::collideWith(Enemy*){
	if (enemyShot) return;

	// destroy bullet
	// enemy health reduction in its own code

	myScene->storeRemovedEntity(this);

}

void Bullet::update(float dt){

	// Move the bullet with the given velocity (speed and rotation angle)
	this->move(speed * cos(this->getRotation()),
		       speed * sin(this->getRotation()));


}