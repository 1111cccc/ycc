#include <list>
#include <string>
#include <iostream>
/*观察者模式，
（第一步先告诉目标我要订阅、取消订阅，目标收到；第二步目标通知订阅者自身的状态）
它定义了一种一对多的关系，让多个观察者对象同时监听某一个主题对象，
这个主题对象的状态发生变化时就会通知所有的观察者对象，使得它们能够自动更新自己。
优点：1、支持简单的广播通信，自动通知所有已经订阅过的对象。
              2、页面载入后目标对象很容易与观察者存在一种动态关联，增加了灵活性。
              3、目标对象与观察者之间的抽象耦合关系能够单独扩展以及重用。
              
              */
class Hero
{
public:
    virtual void update() = 0;
};
class HeroA : public Hero
{
public:
    HeroA()
    {
        std::cout << "A正在打boss" << std::endl;
    }
    virtual void update()
    {
        std::cout << "英雄A原地待机" << std::endl;
    }
};
class HeroB : public Hero
{
public:
    HeroB()
    {
        std::cout << "B正在打boss" << std::endl;
    }
    virtual void update()
    {
        std::cout << "英雄B原地待机" << std::endl;
    }
};
class HeroC : public Hero
{
public:
    HeroC()
    {
        std::cout << "C正在打boss" << std::endl;
    }
    virtual void update()
    {
        std::cout << "英雄C原地待机" << std::endl;
    }
};

class Boss
{
public:
    virtual void attach(Hero* hero) = 0;
    virtual void dafault(Hero* hero) = 0;
    virtual void notify() = 0;
};
class BossA : public Boss
{
public:
    virtual void attach(Hero* hero)
    {
        heroList.push_back(hero);
    }
    virtual void dafault(Hero* hero)
    {
        heroList.remove(hero);
    }
    virtual void notify()
    {
        std::list<Hero *>::iterator it = heroList.begin();
        while(it!=heroList.end())
        {
            (*it++)->update();
        }
    }

private:
    std::list<Hero *> heroList;
};

int main()
{
    Hero* a = new HeroA;
    Hero* b = new HeroB;
    Hero* c = new HeroC;
    Boss *boss = new BossA;
    boss->attach(a);
    boss->attach(b);
    boss->attach(c);
    std::cout << "a阵亡" << std::endl;
    boss->dafault(a);
    std::cout << "boss阵亡" << std::endl;
    boss->notify();
    return 0;
}