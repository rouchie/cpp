#include "3rdparty.h"

// 原子操作
// 所有atomic_xxx都是由 atomic<xxx> typedef来
// typedef atomic<int>			atomic_int;

// atomic 删除了拷贝构造、拷贝赋值，移动构造、移动赋值，是因为无法保证整个拷贝及赋值过程时候原子的，所以删除了这些

std::atomic_int v0{};
int v1 = 0;
std::atomic<int> v2{};
int v3 = 0;

void f0()
{
    for (int i=0; i<100000; i++) {
        v0++;
        v1++;
        v2++;
    }
}

void f1()
{
    // 这里有一点需要注意的，一般来说像下面这种赋值编译器或底层硬件可能优化顺序，但v0是atomic类型，则保证了v0之前所有操作会在v0写入之前完成
    v1 = 1000;
    v3 = 1000;
    v0 = 1000;
}

int main()
{
    spdlog_init();

    createThread(f0);
    createThread(f0);
    createThread(f0);
    createThread(f0);

    ssp(1);

    SPDLOG_INFO("v0[{}] v1[{}] v2[{}]", v0, v1, v2);

    f1();

    return 0;
}