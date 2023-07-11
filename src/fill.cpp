#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v(10);

    show(v, "before fill");

    fill(v.begin(), v.end(), 10);

    show(v, "after fill");

    fill_n(v.begin(), 5, 1024);
    show(v, "after fill_n");

    int i = 10;
    std::generate(v.begin(), v.end(), [&i]() { return ++i; });
    show(v, "after generate");

    std::generate_n(v.begin(), 5, [&i]() { return ++i; });
    show(v, "after generate_n");

    // 跟 go 语言里的 Iota 很像，赋值，递增
    std::iota(v.begin(), v.end(), 10);
    show(v, "after iota");

    return 0;
}