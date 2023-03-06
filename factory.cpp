#include <iostream>
//工厂模式，通过工厂创建对象，而非使用者（尤其很繁琐的实例化）
//优点：实现了类的封闭原则，实现了对象创建和使用的分离（解耦合）
//缺点：类的数量庞大，如果需要增加新的功能，所有类需要改写

//抽象水果
class  Fruit    
{
public:
    virtual void fun() = 0;
    virtual ~Fruit(){}
};
//水果子类，功能具体实现
class Apple : public Fruit
{
public:
     virtual void fun() 
     {
         std::cout << "生产苹果" << std::endl;
     }
};
//水果子类，功能具体实现
class Banan : public Fruit
{
public:
     virtual void fun() 
     {
         std::cout << "生产香蕉" << std::endl;

     }
};
//水果子类，功能具体实现
class Pear : public Fruit
{
public:
     virtual void fun() 
     {
         std::cout << "生产梨子" << std::endl;

     }
};
//抽象工厂
class Factory                                               // 工厂中创建对象
{
public:
    virtual Fruit *CreatFruit()  = 0;
    virtual ~Factory(){}
};
//工厂子类，功能具体实现
class AppleFactory : public Factory
{
public:
    virtual Fruit *CreatFruit()  
    {
         return new Apple;
    }

};
//工厂子类，功能具体实现
class BananFactory : public Factory
{
public:
    virtual Fruit *CreatFruit() 
    {
         return new Banan;
    }

};
//工厂子类，功能具体实现
class PearFactory : public Factory
{
public:
    virtual Fruit *CreatFruit() 
    {
         return new Pear;
    }

};

int main()
{
    Factory *test = new AppleFactory;
    Fruit *obj = test->CreatFruit() ;                                 // 使用者不需要创建对象，只需要调用方法
    obj->fun();
    delete test;
    delete obj;
    return 0;
}
