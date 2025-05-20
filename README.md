# self_registering_factory_proto

解决C++架构中，新增模块与其注册代码耦合问题，同时解决业务与后端切换的耦合，并减少潜在的合作开发代码同步冲突



注册模块：

```c++
//AnimalPool.h
struct Animal {
    virtual ~Animal() = default;
    virtual std::string run() = 0;
    virtual std::string getName() = 0;
    virtual void setArr(int id) = 0;
};

//===========================================================================
//Self-registration factory
class AnimalFactoryRegistry {
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
```

新模块注册（丢入一个cpp文件即可视为增加一个新后端，调用程序中即可使用）

```c++
//bird.cpp
#include"AnimalPool.h"

struct Bird :public Animal {
    //std::string name = "bird";
    static constexpr const char* name = "bird";
    std::string info = "bird .... 2 legs";

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

//
REGISTE_ANIMAL_CRETOR(Bird)
```

调用

```c++
//main.cpp
auto& registry = AnimalFactoryRegistry::getInstance();
std::shared_ptr<Animal> bird_a = registry.createAnimal("bird");
std::shared_ptr<Animal> bird_b = registry.createAnimal("bird");
//两个实例互不干扰
bird_a->setArr(2);
bird_b->setArr(3);
bird_a->run();
bird_b->run();
```


