#include "3rdparty.h"

// 可调用对象包装器
// 1. 包装普通函数
// 2. 包装类的静态函数
// 3. 包装仿函数

void f(int, int)
{
    SPDLOG_INFO("f");
}

class A {
    public:
        static int hello(int) {
            SPDLOG_INFO("static");
            return 0;
        }

        void operator()(int) {
            SPDLOG_INFO("operator()");
        }
};

int main()
{
    spdlog_init();

    // 普通函数
    std::function<void(int)> f0 = [](int) {
        SPDLOG_INFO("f0");
    };
    f0(10);

    // 普通函数
    std::function<decltype(f)> f1 = f;
    f1(1, 2);

    // 类的静态函数
    std::function<int(int)> f2 = A::hello;
    f2(3);

    A a;
    std::function<void(int)> f3 = a;
    f3(1);

    return 0;
}