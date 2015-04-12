#include "spawner.hpp"



Spawner::Spawner(Weapon* weapon, Movement* movement, EnemyTemplate* enemy, std::vector <int> params):
givenWeapon(weapon), givenMovement(movement), enemyData(enemy)
{

	// Need one or two parameters or else the program will quit.
	if (params.size() == 1){
		spawnGapSet = params[0];
	}
	else if (params.size() == 2){

		spawnGapSet = params[0];
		spawnLimit = params[1];
	}
	else {
		exit(1);
	}

}

void Spawner::update(){
	spawn_enemy();
}

void Spawner::spawn_enemy(){
	if (spawnGapTime == 0){
		Enemy* _enemy = new Enemy(enemyData->getScene(),
			enemyData->getTex(),
			enemyData->getHP(),
			enemyData->getSpeed(),
			enemyData->getInvincible(),
			enemyData->getSpawnPos(), new Weapon(*givenWeapon), new Movement(*givenMovement));
		_enemy->getScene()->addEntity(_enemy);
		spawn_count();
		spawnGapTime = spawnGapSet;
	}
	else {
		spawnGapTime--;
	}
}


/*
   Destroy the spawner once entity count reaches 0

   otherwise if set at negative value, spawn them infinitely

   infinte spawning is for test purposes only
*/
void Spawner::spawn_count(){
	if (spawnLimit < 0) return;
	if (spawnLimit > 0) spawnLimit--;
	else {
		delete this;
	}
}