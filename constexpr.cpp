#include "3rdparty.h"

constexpr int size()
{
    return 10;
}

constexpr int rect(int w, int h)
{
    if (w > 10) return h * h;
    return w*h;
}

constexpr int width();

constexpr int height()
{
    constexpr int a = 20;
    return a * a * 3.14;
}

int main()
{
    spdlog_init();

    const int a = 10;
    constexpr int b = 3.14 * a * a;

    SPDLOG_INFO("b[{}] size[{}] width[{}] rect[{}:{}]", b, size(), width(), rect(10, 20), rect(30, 10));

    return 0;
}

constexpr int width()
{
    int a = 10;

    for (int i=0; i<10; i++) {
        a += i;    
    }

    return a;
}