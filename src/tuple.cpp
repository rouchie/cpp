#include "3rdparty.h"

// tuple 可以作为函数返回多个值的时候使用
// 类似go里多返回值

int main()
{
    spdlog_init();

    auto f = []() -> std::tuple<int, std::string> {
        return std::make_tuple(1, "hello");
    };

    auto v = f();

    SPDLOG_INFO("0[{}]", std::get<0>(v));
    SPDLOG_INFO("1[{}]", std::get<1>(v));
    // 越界会包编译错误
    // SPDLOG_INFO("2[{}]", std::get<2>(v));

    auto t = []() -> std::tuple<int, double, long> {
        return std::make_tuple(1, 2.3, 4);
    }();

    SPDLOG_INFO("0[{}]", std::get<0>(t));
    SPDLOG_INFO("1[{}]", std::get<1>(t));
    SPDLOG_INFO("2[{}]", std::get<2>(t));

    return 0;
}