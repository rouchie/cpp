#include "3rdparty.h"

void f(void *)
{
    SPDLOG_INFO("void *");
}

void f(int)
{
    SPDLOG_INFO("int");
}

int main()
{
    spdlog_init();

    // 使用 NULL 调用重载函数，则会报错，因为NULL很多情况下就是 (void*)0 或者直接就是 0
    // error: call of overloaded ‘f(NULL)’ is ambiguous
    // f(NULL);

    f(nullptr);
    f(0);

    return 0;
}