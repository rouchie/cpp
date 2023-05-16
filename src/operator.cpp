#include "3rdparty.h"

class A {
    public:
        // 仿函数的写法
        int operator()(int i) {
            SPDLOG_INFO("i[{}]", i);
            return i;
        }

        // 赋值构造
        A& operator=(const A & a) {
            SPDLOG_INFO("operator= const A &");
            return *this;
        }

        // 移动赋值
        A& operator=(A && a) {
            SPDLOG_INFO("operator= A &&");
            return *this;
        }
};

int main()
{
    spdlog_init();

    A a;
    SPDLOG_INFO("仿函数[{}]", a(20));

    return 0;
}