#pragma once

#include <map>
#include <string>


/*
   We will use this class to store all the names from the weapons folder
   so that certain entities can use it (player, enemy, powerup)

*/

class WeaponManager{
private:
	std::map<std::string, std::string> weapon_map;


public:
	WeaponManager();

	void loadWeapon(std::string&, std::string&);

    // translate ID into reference
	std::string& getFileRef(std::string &name);


};