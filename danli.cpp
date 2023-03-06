#include <iostream>
#include<thread>
#include <mutex>
using namespace std;


class Test
{
public:
    static Test* get()
    {
        return m_test;
    }
    void print()
    {
        cout << "danli" << endl;
    }

private:
    Test() = default;
    Test(const Test &t) = default;
    static Test *m_test;
};
Test *Test::m_test = new Test;
int main()
{
    Test *a = Test::get();
    a->print();
    return 0;
}