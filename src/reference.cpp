#include "3rdparty.h"

// 引用必须立刻初始化，不管是左值引用还是右值引用

int main()
{
    spdlog_init();

    // 左值
    int i = 0;

    // 左值引用
    int & j = i;

    // 右值引用
    int && n = 1;

    // 常量左值引用，可以用任何类型来初始化，左值、右值引用、右值
    const int & z0 = i;
    const int & z1 = n;
    const int & z2 = 2;

    // 常量右值引用, 不可以用左值初始化，只能用右值初始化
    const int && h = 7;

    SPDLOG_INFO("i[{}] j[{}] n[{}]", i, j, n);

    return 0;
}