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

		resetDelay();
	}
}

void Enemy::collideWith(Player* p){

    myScene->storeRemovedEntity(this);

}

void Enemy::collideWith(Bullet* b){
	if (b->getEnemyShot()) return;

	hp--;

	if (hp <= 0) myScene->storeRemovedEntity(this);


}