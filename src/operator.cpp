#include "3rdparty.h"

class A {
    public:
        // 仿函数的写法
        int operator()(int i) {
            SPDLOG_INFO("i[{}]", i);
            return i;
        }
};

int main()
{
    spdlog_init();

    A a;
    SPDLOG_INFO("仿函数[{}]", a(20));

    return 0;
}