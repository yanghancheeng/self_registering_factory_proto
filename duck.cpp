#include"AnimalPool.h"

struct Duck :public Animal {
	static constexpr const char* name = "duck";
	std::string info;

	Duck() {
		info = "duck .... 2 leg";
	}

	std::string run() override final {
		auto rst = info + info;
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

REGISTE_ANIMAL_CRETOR(Duck)
REGISTE_ANIMAL(Duck)
//static AnimalRegister animal_Dog_register("dog", std::make_shared<Duck>());
