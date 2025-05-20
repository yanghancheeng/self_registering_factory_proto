#include "AnimalPool.h"

//==========================
//Singleton self-registration
AnimalRegister::AnimalRegister(std::string name, std::shared_ptr<Animal> ani) {
	AnimalPool().emplace(name, ani);
}

std::map<std::string, std::shared_ptr<Animal>>& AnimalRegister::AnimalPool()
{
	static std::map<std::string, std::shared_ptr<Animal>> animal_pool;
	return animal_pool;
}


//==========================
//Self-registration factory
AnimalFactoryRegistry& AnimalFactoryRegistry::getInstance() {
	static AnimalFactoryRegistry instance;
	return instance;
}

void AnimalFactoryRegistry::registerCreator(const std::string& name, CreatorFunction creator) {
	creators_.try_emplace(name, creator);
}

std::shared_ptr<Animal> AnimalFactoryRegistry::createAnimal(const std::string& name) const {
	auto it = creators_.find(name);
	if (it != creators_.end()) {
		return it->second();
	}
	else {
		std::cout << "no exist Animal: name" << std::endl;
		exit(-1);
	}
}