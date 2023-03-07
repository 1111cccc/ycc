/*模板方法*/
/*父类中抽象出一套操作流程，然后在子类中具体实现*/
/*优点：提取公共行为，放在父类中，实现代码复用*/
#include <iostream>
using namespace std;
//抽象流程
class Operate
{
public:
    void open() const 
    {
        cout << "打开软件" << endl;
    }
    virtual void notice()  = 0;    //特定步骤要在子类实现
    virtual void use()  = 0;         //特定步骤要在子类实现
    void close() const
    {
        cout << "关闭软件" << endl;
    }

    void method()
    {
        open();
        notice();
        use();
        close();
    }
};
class Pdf :public Operate
{
public:
    virtual void notice()  override
    {
        cout << "Pdf注意事项" << endl;
    }
    virtual void use() 
    {
        cout << "pdf使用守则" << endl;
    }
};
class Word : public Operate
{
public:
    virtual void notice()  override
    {
        cout << "word注意事项" << endl;
    }
    virtual void use() 
    {
        cout << "word使用守则" << endl;
    }
};
int main()
{
    Operate *pdf = new Pdf;
    pdf->method();
    return 0;
}