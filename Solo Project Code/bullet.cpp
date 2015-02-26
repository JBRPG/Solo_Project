#include "bullet.hpp"

void Bullet::collideWith(Player*){
	if (!enemyShot) return;

	// Reduce hp on the player from the bullet

	// Make the bullet desroyed afterwards

}

void Bullet::collideWith(Enemy*){
	if (enemyShot) return;

	// Reduce hp on the enemy from the bullet

}

void Bullet::update(float dt){

	// Move the bullet with the given velocity (speed and rotation angle)
	this->move(speed * cos(this->getRotation()),
		       speed * sin(this->getRotation()));


}