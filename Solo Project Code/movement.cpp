#include "movement.hpp"

void Movement::updateMovement(Entity& entity, std::string name){






}

// First look up the table of function pointers to find its name
// if the name is not found after the search, stop program
// and tell the user "movement name not found"

void Movement::lookupMovement(Entity& entity, std::string name){

	static std::map < std::string, void (Movement::*)
		(Entity&, sf::Vector2f, std::vector<float>) >  table
	{
		{"stright", &Movement::straight},
		{"circle", &Movement::circle},
		{"sine", &Movement::sinusodial}
	};

	auto entry = table.find(name);
	if (entry != table.end()){
		(this->*(entry->second))(entity, coordinates, args);
	}
	else {
		std::cerr << "Cannot find movement with the name " << name << std::endl;
	}



}



// for each individual function involving movement,
// Check that the correct number of float arguments are there.
// if the number of arguments are incorrect,
// then stop the program and tell the user
// the correct array size and its arguments in order.

void Movement::circle(Entity& entity, sf::Vector2f vertex, std::vector<float> params){
	// The circle shall have one float argument
	if (params.size() != 1){
		std::cerr << "Need only one constant float value for circle: radius" << std::endl;
	}
	float pi = 3.14;
	float deg_to_rad = pi / 180;
	entity.setPosition(
		params[0] * cos(entity.getTicks() * deg_to_rad) + vertex.x,
		params[0] * sin(entity.getTicks() * deg_to_rad) + vertex.y);


}

void Movement::straight(Entity& entity, sf::Vector2f vertex, std::vector<float> params){
	

}

void Movement::sinusodial(Entity& entity, sf::Vector2f vertex, std::vector<float> params){


}