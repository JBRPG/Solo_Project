#include "movement.hpp"

// might end up trying to make the parameter a pointer
// if it fixes the inheritence value problem
// which entity& has the data from its subclass, but returns 0
// from its public functions (ie. getSpeed, getPosition)

void Movement::update(Entity& entity){

	lookupMovement(entity, this->name);

}

// First look up the table of function pointers to find its name
// if the name is not found after the search, stop program
// and tell the user "movement name not found"

void Movement::lookupMovement(Entity& entity, std::string name){

	static std::map < std::string, void (Movement::*)
		(Entity&, sf::Vector2f, std::vector<float>) >  table
	{
		{"straight", &Movement::straight},
		{"circle", &Movement::circle},
		{"sine", &Movement::sinusodial}
	};

	auto entry = table.find(name);
	if (entry != table.end()){
		(this->*(entry->second))(entity, coordinates, args);
	}
	else {
		std::cerr << "Cannot find movement with the name " << name << std::endl;
		std::exit(1);
	}



}



// for each individual function involving movement,
// Check that the correct number of float arguments are there.
// if the number of arguments are incorrect,
// then stop the program and tell the user
// the correct array size and its arguments in order.

void Movement::circle(Entity& entity, sf::Vector2f vertex, std::vector<float> params){
	if (params.size() != 1){
		std::cerr << "Need only one float value for circle: radius" << std::endl;
		return;
	}
	float pi = 3.14;
	float deg_to_rad = pi / 180;

	// This has no problems since entity itself has ticks
	entity.setPosition(
		params[0] * cos(entity.getTicks() * deg_to_rad) + vertex.x,
		params[0] * sin(entity.getTicks() * deg_to_rad) + vertex.y);


}

void Movement::straight(Entity& entity, sf::Vector2f vertex, std::vector<float> params){
	if (params.size() != 1){
		std::cerr << "Need only one float value for stright: angle" << std::endl;
		return;
	}

	float pi = 3.14;
	float deg_to_rad = pi / 180;

	// This has problems since entity itself, not subclasses return 0 from public functions
	entity.move(entity.getSpeed() * cos(params[0] * deg_to_rad),
		        entity.getSpeed() * sin(params[0] * deg_to_rad));


}

void Movement::sinusodial(Entity& entity, sf::Vector2f vertex, std::vector<float> params){

	if (params.size() != 2){
		std::cerr << "Need two float values for sine: " <<
			"amplitude(0) and period(1)" << std::endl;
		return;
	}

	float pi = 3.14;

	/* since it is a horizontal shooting game,
	   we will move forward with x
	   and use sine movement on y
	*/

	entity.setPosition(

		// only for x
		// This has problems since entity itself, not subclasses return 0 from public functions
		entity.getPosition().x + entity.getSpeed(),
		params[0] * sin( (pi / 2) * params[1] * entity.getTicks()) + vertex.y);

}