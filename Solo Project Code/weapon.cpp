#include "weapon.hpp"


/*
  Construct a weapon by having a vector of bullets with a given keyword
  A weapon will have a given delay time between shooting with the weapon
  A specific cooldown will be used based on the given keyword.


*/
Weapon::Weapon(std::vector <BulletTemplate> bullets, std::string key_name, int delay, std::vector<int> key_params) :
bullet_list(bullets), keyword(key_name), shootCooldownSet(delay)
{
	if (keyword == "rapid_player" || keyword == "rapid_enemy"){
		rapidRateSet = key_params[0];
		rapidDurationSet = key_params[1];
	}

	if (keyword == "hold_player") holdDurationSet = key_params[0];

	if (keyword == "sequence_enemy") sequenceDelaySet = key_params[0];
}


// When an entity shoots bullets, we will find out if its a player or enemy
// to determine who shot them

void Weapon::shootBullets(Entity& shooter){
	
	if (Enemy* enemy = dynamic_cast<Enemy*> (&shooter)){
		enemydidShoot = true;
	}
	else if (Player* player = dynamic_cast<Player*> (&shooter)){
		enemydidShoot = false;
	}

	for (auto bullet_data : bullet_list){
		Bullet* bullet_p = new Bullet(shooter.getScene()->
			game->texmgr.getRef(bullet_data.getTex()),
			bullet_data.getHP(),
			bullet_data.getSpeed(),
			bullet_data.getInvincible(),
			enemydidShoot,
			bullet_data.getRotation() + (180 * enemydidShoot));
		int shootFlip = enemydidShoot ? -1 : 1;
		bullet_p->setPosition(shooter.getPosition().x + (shootFlip * shooter.getGlobalBounds().width / 2),
			shooter.getPosition().y);
		shooter.getScene()->storeAddedEntity(bullet_p);
	}

<<<<<<< HEAD
}

// Shoot a single bullet
void Weapon::shootBullet(Entity& shooter, BulletTemplate& bullet){
	if (Enemy* enemy = dynamic_cast<Enemy*> (&shooter)){
		enemydidShoot = true;
	}
	else if (Player* player = dynamic_cast<Player*> (&shooter)){
		enemydidShoot = false;
	}

	Bullet* bullet_p = new Bullet(
		shooter.getScene()->game->texmgr.getRef(bullet.getTex()),
		bullet.getHP(),
		bullet.getSpeed(),
		bullet.getInvincible(),
		enemydidShoot,
		bullet.getRotation() + (180 * enemydidShoot));
	int shootFlip = enemydidShoot ? -1 : 1;
	bullet_p->setPosition(shooter.getPosition().x + (shootFlip * shooter.getGlobalBounds().width / 2),
		shooter.getPosition().y);
	shooter.getScene()->storeAddedEntity(bullet_p);


}

void Weapon::singleShot(Entity& shooter){

	// If entity is player, then cooldown will activate when player holds down fire key
	// otherwise cooldown will reset to 0, to allow rapid pressing.

	if (Player* player = dynamic_cast<Player*> (&shooter)){
		if (Input::instance()->pressKeybutton(sf::Keyboard::Space)){

			if (shootCooldownTime == 0){
				shootBullets(shooter);
				shootCooldownTime = shootCooldownSet;
			}

			else {
				shootCooldownTime--;
			}
		}
		else {
			shootCooldownTime = 0;
		}
	}

	if (Enemy* enemy = dynamic_cast<Enemy*> (&shooter)){
		if (shootCooldownTime == 0){
			shootBullets(shooter);
			shootCooldownTime = shootCooldownSet;
		}

		else {
			shootCooldownTime--;
		}
	}

}

void Weapon::rapidFire(Entity& shooter){
	if (rapidWait == 0){
		shootBullets(shooter);
		rapidWait = rapidWaitSet;
	}
	else {
		rapidWait--;
	}
}

void Weapon::rapidEnemy(Entity& shooter){
	if (shootCooldownTime == 0){

		if (rapidDuration == 0){
			shootCooldownTime = shootCooldownSet;
			rapidDuration = rapidDurationSet;

		}
		else {
			rapidFire(shooter);
			rapidDuration--;
		}

	}
	else shootCooldownTime--;
}

void Weapon::rapidPlayer(Entity& shooter){
	
	if (Input::instance()->pressKeybutton(sf::Keyboard::Space)){
		if (shootCooldownTime == 0){

			if (rapidDuration == 0){
				shootCooldownTime = shootCooldownSet;
				rapidDuration = rapidDurationSet;

			}
			else {
				rapidFire(shooter);
				rapidDuration--;
			}

		}
		else shootCooldownTime--;
	}
	else {
		shootCooldownTime = 0;
	}
}

void Weapon::holdPlayer(Entity& shoter){}

void Weapon::sequenceFire(Entity& shooter){

	if (sequenceDelayTime == 0){

		if (sequence_idx < bullet_list.size()){
			shootBullet(shooter, *bullet_list[sequence_idx]);
			sequenceDelayTime = sequenceDelaySet;
			sequence_idx++;
		}
		else {
			shootCooldownTime = shootCooldownSet;
			sequence_idx = 0;
		}
	}
	else {
		sequenceDelayTime--;
	}

}

void Weapon::sequenceEnemy(Entity& shooter){
	if (shootCooldownTime == 0){
			sequenceFire(shooter);
	}
	else shootCooldownTime--;
=======
>>>>>>> parent of 8ecfb12... Weapon Class Finished
}