#include"AnimalPool.h"

struct Dog :public Animal {
	static constexpr const char* name = "dog";

	std::string info;

	Dog() {
		info = "dog .... 4 leg";
	}

	std::string run() override final {
		auto rst = info;
		std::cout << rst << " id=" << id_ << std::endl;
		return rst;
	}
	std::string getName() override final {
		return name;
	}

	int id_ = 0;
	void setArr(int id) override final {
		id_ = id;
	}
};
REGISTE_ANIMAL_CRETOR(Dog)
REGISTE_ANIMAL(Dog)
//static AnimalRegister animal_Dog_register("dog", std::make_shared<Dog>());
