#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::queue<int> q;

    q.emplace(1);
    q.push(2);

    SPDLOG_INFO("size: {} front: {} back: {}", q.size(), q.front(), q.back()); 

    q.pop();

    SPDLOG_INFO("size: {} front: {} back: {}", q.size(), q.front(), q.back()); 

    SPDLOG_INFO("empty: {}", q.empty());

    std::queue<int> q0;
    q0.push(1);
    q0.push(2);
    q0.push(3);
    q0.push(4);
    q0.push(5);

    q.swap(q0);

    SPDLOG_INFO("s size[{}] s0 size[{}]", q.size(), q0.size());

    return 0;
}