#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::stack<int> s;

    s.emplace(1);
    s.push(2);

    SPDLOG_INFO("size: {} top: {}", s.size(), s.top()); 

    s.pop();

    SPDLOG_INFO("size: {} top: {}", s.size(), s.top()); 

    SPDLOG_INFO("empty: {}", s.empty());

    std::stack<int> s0;
    s0.push(1);
    s0.push(2);
    s0.push(3);
    s0.push(4);
    s0.push(5);

    s.swap(s0);

    SPDLOG_INFO("s size[{}] s0 size[{}]", s.size(), s0.size());

    return 0;
}