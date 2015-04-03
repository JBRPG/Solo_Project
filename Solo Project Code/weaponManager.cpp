#include "weaponManager.hpp"

void WeaponManager::loadWeapon( std::string &name, std::string &filename){

	// Add to the list, we will use the weapon to call out the file itself
	// to create unique bullets
	this->weapon_map[name] = filename;

}

std::string& WeaponManager::getFileRef(std::string& name){
	return this->weapon_map.at(name);
}