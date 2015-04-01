#include "weapon.hpp"


/*
  Construct a weapon by having a vector of bullets with a given keyword
  A weapon will have a given delay time between shooting with the weapon
  A specific cooldown will be used based on the given keyword.


*/
Weapon::Weapon(std::vector <Bullet> bullets, std::string key_name, int delay, int key_param):
bullet_list(bullets), keyword(key_name), shootCooldownSet(delay)
{
	if (keyword == "rapid_player" || keyword == "rapid_enemy")
		rapidDurationSet = key_param;

	if (keyword == "hold_player") holdDurationSet = key_param;

	if (keyword == "sequence_enemy") sequenceDelaySet = key_param;


}