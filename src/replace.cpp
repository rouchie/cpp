#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v(10);

    int i = 10;
    std::generate(v.begin(), v.end(), [&i]() { return ++i; });
    show(v, "after generate");

    // 替换，把15替换成1024
    std::replace(v.begin(), v.end(), 15, 1024);
    show(v, "after replace");

    std::replace_if(v.begin(), v.end(), [](int e) { return e == 17; }, 1024);
    show(v, "after replace_if");

    return 0;
}