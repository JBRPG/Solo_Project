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