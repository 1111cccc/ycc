/*代理模式*/
/*为其他对象提供一种代理，以控制对这个对象的访问*/
/*代理将自己伪装成真正的对象。*/
/*访问外网，需要代理服务器
在代理中可以增加访问权限，（类似登录密码）
可以增加日志，并且客户可以通过代理完成同样的访问*/
#include <iostream>
using namespace std;

//中央系统，真正的系统接口
class CenterSystem
{
public:
    virtual void run()  = 0;
    
};
//真正的系统
class RealSystem:public CenterSystem
{
public:
    virtual void run()  override
    {
        cout << "系统启动成功" << endl;
    }
};

// 代理
class Proxy :public CenterSystem
{
public:
    //设置密码访问
    Proxy(string password):m_password(password){}
    bool check()
    {
        if (m_password == "ycc")
        {
            return true;
        }
        return false;
    }
    virtual void run()  override
    {
        if(check())
        {
            m_real = new RealSystem;
            cout << "验证通过，使用代理启动：" << endl;
            m_real->run();
            delete m_real;
        }
        else
        {
            cout << "密码错误" << endl;
        }
    }

private:
    string m_password;
    RealSystem *m_real;

};
int main()
{
    //直接启动
    RealSystem *real = new RealSystem;
    real->run();
    // 代理启动
    Proxy *proxy = new Proxy("ycc");          //密码ycc
    proxy->run();
    return 0;
}