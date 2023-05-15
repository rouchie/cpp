#include "3rdparty.h"

// 绑定器

// 1. 将可调用对象和参数绑定成一个仿函数
// 2. 绑定部分参数

class A {
    public:
        void hello(int i, int j) {
            SPDLOG_INFO("hello i[{}] j[{}]", i, j);
        }

        void world(std::string name, int age) {
            SPDLOG_INFO("world name[{}] age[{}]", name, age);
        }
};

int main()
{
    spdlog_init();

    auto f = [](int i, int j) {
        SPDLOG_INFO("i[{}] j[{}]", i, j);
    };

    auto f0 = std::bind(f, 1, 2);
    f0();

    // TD<decltype(f0)> td;

    auto f1 = std::bind(f, 1, std::placeholders::_1);
    f1(3);

    auto f2 = std::bind(f, std::placeholders::_1, 10);
    f2(3);

    A a;
    // 注意函数也需要 &
    auto f3 = std::bind(&A::hello, &a, 1, 2);
    f3();

    // 这里用了 _2, 表示 _1没用到，直接用2了，所以函数调用时需要两个参数，但第一个参数浪费了
    auto f4 = std::bind(&A::world, &a, "rouchie", std::placeholders::_2);
    f4(1, 2);

    return 0;
}