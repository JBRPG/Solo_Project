#include "enemy.hpp"


void Enemy::update(float dt){
	shootEnemy(dt);
}


void Enemy::shootEnemy(float dt){
	shootDelay -= dt;

	if (shootDelay <= 0.0f){

		Bullet* bullet_p = new Bullet(myScene->game->texmgr.getRef("bulletEnemy"),
			1, 10, false, true, 180.0f);


		bullet_p->setPosition(this->getPosition().x - this->getGlobalBounds().width / 2,
			this->getPosition().y);
		myScene->storeAddedEntity(bullet_p);
		bullet_p->setEnemyShot(true);

		resetDelay();
	}
}

void Enemy::collideWith(Entity &other){

	if (Player* player = dynamic_cast<Player*>(&other)){

		destroyEnemy();
	}
	else if (Bullet* bullet = dynamic_cast<Bullet*>(&other)) {
		if (bullet->getEnemyShot()) return;

		hp--;

		if (hp <= 0){
			destroyEnemy();


		}
	}
}

void Enemy::destroyEnemy(){
	myScene->storeRemovedEntity(this);

	Explosion* explode = new Explosion
		(myScene->game->texmgr.getRef("explodeTest"), 0);
    explode->setSpawnTime(1.0f);
	explode->setPosition(this->getPosition().x - this->getGlobalBounds().width / 2,
		this->getPosition().y);

	myScene->addEntity(explode); // you have to actually add the entity because
	                             // storeAdded list has already been checked during update
}