#pragma once

#include "SFML\Graphics.hpp"


#include <functional>
#include <iostream>


#include "entity.hpp"

/*
    Movement class allows any non-playable entities (enemy, bullet, etc.)
	to have a pre-defined movement based on the following parameters:

	'*' denotes optional since some movements are very simple, like linear

	  String: "name" - search the name on the collection of movement patterns.
	          if the name matches the pattern, a specified function will be called
			  to give the entity movement
	* Vector2f: coordinates ([0],[1]) - (x,y) or (y,x).
	          The first index of vector2f will be used
			  as primary movement axis (x or y).
			  The second index will be reserved for
			  more complicated movements (y or x).
	  float []: initializer parameters - depending on formula, more variables
	          will be needed inside the array.
			  Along with the name being searched, the array must have the correct amount
			  of elements to get a specific function
*/


/*
   This file will also make use of function pointers,
   a helpful, but rarely used technique in C++.
   
   Function Pointers are like pointers, but have some special rules
   to use them correctly. One special rule is that pointers to functions
   CANNOT be dereferenced, if they are used as an argument.
   
   To declare a function pointer, it must have the following:

   std::function<returnType (Arguments) *funcPtr>

   For the function pointer to work, there must be functions
   that match the same return type and its arguments

   example:

   std::function<int (int, int)> *mathOp; // required return and argument types

   // matching return and argument types
   int add(int a, int b) {return a + b;};
   int sub(int a, int b) {return a - b;};

   main (){

   std::function <int (int, int)> *plus = &add;
   std::function <int (int, int)> *minus = &sub;

   std::cout << "add function: " << (*plus) (2,3) << endl;
   std::cout << "add function: " << (*minus) (2,3) << endl;


   }

*/

class Movement {

private:
	std::vector<float> args;
	std::string name;
	sf::Vector2f coordinates;


	// The function pointer used for calling functions based on name
	std::function <void(std::string, sf::Vector2f, std::vector<float>)> *movementType;


public:

	// Constructor

	// Constructor
	Movement(std::string name, sf::Vector2f vertex, std::vector<float>args) :
		name{ name }, coordinates{ vertex }, args{ args }
	{

	};

	void updateMovement(Entity&, std::string);

	void setName(std::string name) { this->name = name; };
	void setEntityVertex(sf::Vector2f vec) { coordinates = vec; };
	void setFloatArgs(std::vector<float> args) { this->args = args; };


	void lookupMovement(Entity&, std::string);

	// Functions used to define specific movements for entities
	// Will be used for function lookup table

	/* The required parameters are in order:
	   1 - Entity&: need the entity to move it
	   2 - sf::Vector2f: vertex will be used for some complex equations
	   3 - float*: number of float values for equations
	*/
	void circle(Entity&, sf::Vector2f, std::vector<float>);
	void straight(Entity&, sf::Vector2f, std::vector<float>);
	void sinusodial(Entity&, sf::Vector2f, std::vector<float>);



};