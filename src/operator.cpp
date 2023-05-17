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

// 字符串字面量自定义

std::string operator"" _hello(const char *s, size_t len)
{
    return std::string(s) + ", hello";
}

std::string operator"" _world(unsigned long long v)
{
    return std::to_string(v) + ", world";
}

int main()
{
    spdlog_init();

    std::string hello = "rouchie"_hello;
    SPDLOG_INFO("{}", hello);

    std::string world = 1024_world;
    SPDLOG_INFO("{}", world);

    A a;
    SPDLOG_INFO("仿函数[{}]", a(20));

    return 0;
}