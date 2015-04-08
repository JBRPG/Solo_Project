#include "bullet.hpp"


/*
For all entity comparisons, we will use dynamic_cast
with the reference to Entity object - Entity& other
to keep code cleaner

dynamic_cast to a pointer type returns NULL if the cast fails
dynamic_cast to a reference type would throw an exception on failure
*/

void Bullet::collideWith(Entity& other){

	if (Player* player = dynamic_cast<Player*>(&other)){
		if (!enemyShot) return;

		// destroy the bullet
		// player health reduction taken care of
		// in Player's code

		myScene->storeRemovedEntity(this);
	}
	else if (Enemy* enemy = dynamic_cast<Enemy*>(&other)){
		if (enemyShot) return;

		// destroy bullet
		// enemy health reduction in its own code

		myScene->storeRemovedEntity(this);
	}
}


void Bullet::update(float dt){

	// Since math functions take radians for sine and cosine,
	// we had to covnert from degrees to radians through the variables below

	float pi = 3.14;
	float deg_to_rad = pi / 180.0f;

	// Move the bullet with the given velocity (speed and rotation angle)
	this->move(speed * cos(this->getRotation() * deg_to_rad),
		       speed * sin(this->getRotation() * deg_to_rad));


}