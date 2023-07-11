#include "3rdparty.h"

// deque 和 vector 不同，不是数组的形式存放，操作要比vector慢
// 提供随机访问迭代器

int main()
{
    spdlog_init();
    std::deque<int> d;

    int i = 0;
    std::generate_n(std::front_inserter(d), 10, [&i]() {
        return ++i;
    });

    show(d, "front insert");

    std::generate_n(std::back_inserter(d), 10, [&i]() {
        return ++i;
    });

    show(d, "back insert");

    return 0;
}