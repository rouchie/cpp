#include "3rdparty.h"

// constexpr 常量表达式
// c++11 对常量表达式比较严格，很多情况下无法使用
// c++14 则不一样，很宽松

// 递归竟然也可以
constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}

constexpr int size()
{
    return 10;
}

constexpr int rect(int w, int h)
{
    if (w > 10) return h * h;
    return w*h;
}

constexpr int width();

constexpr int height()
{
    constexpr int a = 20;
    return a * a * 3.14;
}

int main()
{
    spdlog_init();

    SPDLOG_INFO("fibonacci(10) [{}]", fibonacci(10));

    char arr[fibonacci(10)] = "www.rouchie.com";
    SPDLOG_INFO("arr[{}]", arr);

    const int a = 10;
    constexpr int b = 3.14 * a * a;

    SPDLOG_INFO("b[{}] size[{}] width[{}] rect[{}:{}]", b, size(), width(), rect(10, 20), rect(30, 10));

    return 0;
}

constexpr int width()
{
    int a = 10;

    for (int i=0; i<10; i++) {
        a += i;    
    }

    return a;
}