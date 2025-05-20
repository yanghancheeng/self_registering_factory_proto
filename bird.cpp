#include"AnimalPool.h"

struct Bird :public Animal {
	//std::string name = "bird";
	static constexpr const char* name = "bird";
	std::string info = "bird .... 2 leg";

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

REGISTE_ANIMAL_CRETOR(Bird)
REGISTE_ANIMAL(Bird)
//static AnimalRegister animal_Bird_register("bird", std::make_shared<Bird>());
