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

    std::vector<int> v {1, 2, 3};

    std::for_each(std::begin(v), std::end(v), [](int & i) {
        SPDLOG_INFO("value [{}]", i);
    });

    std::for_each(m.begin(), m.end(), [](const std::pair<int, std::string>& pair) {
        SPDLOG_INFO("first[{}] second[{}]", pair.first, pair.second);
    });

    // 下面的写法错误，必须加上const
    // 因为map的key不可以改动，所以必须带上const
    // std::for_each(m.begin(), m.end(), [](std::pair<int, std::string>& pair) {});


    return 0;
}