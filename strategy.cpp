/*策略模式
同样执行一种事情，因为内部算法不同导致结果不同
可以使算法独立于使用它的客户而变化*/
#include <iostream>
using namespace std;
class Weapen
{
public:
    virtual void heat() const = 0;
};
class Knife : public Weapen
{
    virtual void heat() const override
    {
        cout << "刀子的伤害" << endl;
    }
};
class AK : public Weapen
{
    virtual void heat() const override
    {
        cout << "AK的伤害" << endl;
    }
};

class Strategy
{
public:
    //使用构造函数传入参数
    Strategy(Weapen *weapen)
    {
        m_weapen = weapen;
    }
    //使用函数方法传参
    void setWeapen(Weapen *weapen)
    {
        m_weapen = weapen;
    }
    void use()
    {
        m_weapen->heat();
    }

private:
    Weapen *m_weapen;
};

int main ()
{
    Weapen *knife = new Knife;
    Weapen *ak = new AK;
    //用自己设置的构造函数
    Strategy *obj = new Strategy(ak);
    obj->use();
    cout << endl;
    //不用构造函数
    Strategy *obj2= new Strategy(ak);
    obj2->setWeapen(knife);
    obj2->use();

    delete ak;
    delete obj;
    delete knife;
    delete obj2;
    return 0;
}