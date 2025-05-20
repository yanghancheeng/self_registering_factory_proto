#pragma once
#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <functional>

struct Animal {
	virtual ~Animal() = default;
	virtual std::string run() = 0;
	virtual std::string getName() = 0;
	virtual void setArr(int id) = 0;
};

//===========================================================================
//Singleton self-registration
class AnimalRegister {
public:
	AnimalRegister(std::string, std::shared_ptr<Animal> pplugin);
	static std::map<std::string, std::shared_ptr<Animal>>& AnimalPool();
};
#define REGISTE_ANIMAL(CLASS_NAME) \
	static AnimalRegister animal_##CLASS_NAME##_register(CLASS_NAME::name,std::make_shared<CLASS_NAME>());


//===========================================================================
//Self-registration factory
class AnimalFactoryRegistry {
private:
	AnimalFactoryRegistry() = default;
    ~AnimalFactoryRegistry() = default;
public:
	using CreatorFunction = std::function<std::shared_ptr<Animal>()>;
	
	AnimalFactoryRegistry(const AnimalFactoryRegistry&) = delete;
    AnimalFactoryRegistry& operator=(const AnimalFactoryRegistry&) = delete;
    static AnimalFactoryRegistry& getInstance();
	
	void registerCreator(const std::string& name, CreatorFunction factory);
	std::shared_ptr<Animal> createAnimal(const std::string& name) const;

private:
	std::map<std::string, CreatorFunction> creators_;
};

template <typename T>
class AnimalCtrAutoEnroller {
public:
	AnimalCtrAutoEnroller() {
		AnimalFactoryRegistry::getInstance().registerCreator(T::name, []() {
			return std::make_shared<T>();
			});
	}
};

#define REGISTE_ANIMAL_CRETOR(CLASS_NAME) \
    static AnimalCtrAutoEnroller<CLASS_NAME> registrar##CLASS_NAME;