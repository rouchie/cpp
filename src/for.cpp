#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::map<int, std::string> m;

    m[0] = "hello";
    m[1] = "world";
    m[2] = "ni";
    m[3] = "hao";

    // 会拷贝，不可以直接修改值
    for (auto v : m) {
        SPDLOG_INFO("{} - {}", v.first, v.second);
    }

    // 不会拷贝，并且可以直接修改值
    for (auto & v : m) {
        SPDLOG_INFO("{} - {}", v.first, v.second);
        v.second = fmt::format("{}", getUS());
    }

    // 不会拷贝，不可以直接修改值
    for (const auto & v : m) {
        SPDLOG_INFO("{} - {}", v.first, v.second);
        // v.second = fmt::format("{}", getUS());
    }

    for (auto && v : m) {
        SPDLOG_INFO("{} - {}", v.first, v.second);
        v.second = fmt::format("{}", getUS());
    }

    for (auto && v : m) {
        SPDLOG_INFO("{} - {}", v.first, v.second);
    }

    return 0;
}