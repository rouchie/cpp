#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v(10);

    int i = 10;
    std::generate(v.begin(), v.end(), [&i]() { return ++i; });
    show(v, "after generate");

    // 可以直接在自己身上转换
    std::transform(v.begin(), v.end(), v.begin(), [](int e) { return e*2; });
    show(v, "after transform");

    // 也可以转换到其他容器上
    std::vector<int> v1(v.size());
    std::transform(v.begin(), v.end(), v1.begin(), [](int e) { return e*2; });
    show(v1, "after transform");

    return 0;
}