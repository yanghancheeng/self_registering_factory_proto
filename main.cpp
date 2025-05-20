#include <iostream>
#include <vector>
#include <algorithm>

#include "AnimalPool.h"
using namespace std;


int main(){
	// ** traditional factory model **
	//
	//AnimalFactory animalFactory;
	//Animal* ani = animalFactory.getAnimal("dog");
	//ani->run();
	//
	//ani = animalFactory.getAnimal("duck");
	//ani->run();
	//
	//ani = animalFactory.getAnimal("mouse");
	//ani->run();

	// init
	auto ani_pool = AnimalRegister::AnimalPool();
	auto& registry = AnimalFactoryRegistry::getInstance();

	
	// Self-registration pattern
	std::shared_ptr<Animal> ani;
	ani = ani_pool.at("dog");
	ani->run();
	ani = ani_pool.at("duck");
	ani->run();
	// This is naturally singleton, can never get a second different Bird object
	std::shared_ptr<Animal> bird_0 = ani_pool.at("bird");
	std::shared_ptr<Animal> bird_1 = ani_pool.at("bird");
	bird_0->setArr(100);
	bird_1->setArr(200);
	bird_0->run();
	bird_1->run();

	//==============================================================

	// Using self-registration factory pattern to remove the natural singleton constraint
	std::shared_ptr<Animal> bird_a = registry.createAnimal("bird");
	std::shared_ptr<Animal> bird_b = registry.createAnimal("bird");
	bird_a->setArr(2);
	bird_b->setArr(3);
	bird_a->run();
	bird_b->run();

	// Free to create any animal
	std::shared_ptr<Animal> animal_ptr;
	animal_ptr = registry.createAnimal("duck");
	animal_ptr->run();
	animal_ptr = registry.createAnimal("bird");
	animal_ptr->run();
	animal_ptr = registry.createAnimal("dog");
	animal_ptr->run();

	return 0;
}
