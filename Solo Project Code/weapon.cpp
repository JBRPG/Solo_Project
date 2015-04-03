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

}