#include "3rdparty.h"

// 引用必须立刻初始化，不管是左值引用还是右值引用
// 常量左值引用称为万能引用，可以任何值来初始化

class A {
    public:
        A() {
            SPDLOG_INFO("A");
        }
        ~A() {
            SPDLOG_INFO("~A");
        }
        A(const A& a) {
            SPDLOG_INFO("const A&");
        }
        A(A&& a) {
            SPDLOG_INFO("A&&");
        }
        A& operator=(const A& a) {
            SPDLOG_INFO("operator const A&");
            return *this;
        }
        A& operator=(A&& a) {
            SPDLOG_INFO("operator A&&");
            return *this;
        }

        void hello() {}
};

A getA()
{
    return A();
}

A&& getA1()
{
    A a;
    return std::move(a);
}

int main()
{
    spdlog_init();

    // 左值
    int i = 0;

    // 左值引用
    int & j = i;

    // 右值引用
    int && n = 1;

    // 常量左值引用，可以用任何类型来初始化，左值、右值引用、右值
    const int & z0 = i;
    const int & z1 = n;
    const int & z2 = 2;

    // 常量右值引用, 不可以用左值初始化，只能用右值初始化
    const int && h = 7;

    SPDLOG_INFO("i[{}] j[{}] n[{}] {} {} {} {}", i, j, n, z0, z1, z2, h);

    A a0 = getA();
    A && a1 = getA();
    A a2 = a0;
    A && a3 = getA1();

    a0.hello();
    a1.hello();
    a2.hello();
    a3.hello();

    return 0;
}