#include "3rdparty.h"

// c++11 之前的写法
template <typename T, typename R, typename Z>
Z add0(T t, R r)
{
    return t+r;
}

// c++11 写法，尾随返回类型
template <typename T, typename R>
auto add1(T t, R r) -> decltype(t+r)
{
    return t+r;
}

// c++14 写法
template <typename T, typename R>
auto add2(T t, R r)
{
    return t+r;
}

int main()
{
    spdlog_init();

    SPDLOG_INFO("add0 {}", add0<int, double, double>(1, 2.3));
    SPDLOG_INFO("add1 {}", add1(4, 5.6));
    SPDLOG_INFO("add2 {}", add2(7, 8.9));

    return 0;
}