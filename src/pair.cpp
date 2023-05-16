#include "3rdparty.h"

int main()
{
    spdlog_init();

    {
        auto p = std::make_pair<double, std::string>(1, "hello");
        SPDLOG_INFO("first[{}] second[{}]", p.first, p.second);
        // TD<decltype(p)> td;
    }

    {
        auto p = std::make_pair(1., "hello");
        SPDLOG_INFO("first[{}] second[{}]", p.first, p.second);
        // TD<decltype(p)> td;
    }

    std::map<int, std::string> m;
    m.emplace(1, "hello");
    m.insert(std::make_pair(2, "world"));

    for (auto & v : m) {
        SPDLOG_INFO("v first[{}] second[{}]", v.first, v.second);
    }

    return 0;
}