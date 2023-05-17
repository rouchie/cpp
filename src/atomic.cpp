#include "3rdparty.h"

// 原子操作
// 所有atomic_xxx都是由 atomic<xxx> typedef来
// typedef atomic<int>			atomic_int;

std::atomic_int v0{};
int v1 = 0;
std::atomic<int> v2{};

void f0()
{
    for (int i=0; i<100000; i++) {
        v0++;
        v1++;
        v2++;
    }
}

int main()
{
    spdlog_init();

    createThread(f0);
    createThread(f0);
    createThread(f0);
    createThread(f0);

    ssp(2);

    SPDLOG_INFO("v0[{}] v1[{}] v2[{}]", v0, v1, v2);

    return 0;
}