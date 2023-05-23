#include "3rdparty.h"

/*
在 C++ 中，volatile 是一个关键字，用于告诉编译器，某个变量的值可能会在程序的其他地方被修改，因此每次读取该变量时，都应该从内存中读取，而不是从寄存器中读取。

具体来说，volatile 可以用于以下场景：

多线程并发访问同一内存地址的情况。

访问硬件寄存器或其他外设，这些寄存器的值可能会被硬件或其他线程修改。

优化时避免编译器过度优化，例如某个变量在程序中没有被修改，但是在其他线程中被修改了，如果没有使用 volatile，编译器可能会将该变量的值缓存在寄存器中，导致程序出错。

需要注意的是，使用 volatile 可能会影响程序的性能，因为每次读取变量时都需要从内存中读取，而不是从寄存器中读取，因此应该谨慎使用。
同时，volatile 不能保证线程安全，如果需要保证线程安全，应该使用互斥锁等线程同步机制。
*/

// 并不能线程安全，只是运行时从内存读值，而不是从寄存器读值
volatile uint32_t value = 0;

void f()
{
    for (int i=0; i<1000;i++) {
        value++;
        value++;
    }
}

int main()
{
    spdlog_init();

    createThread(f);
    createThread(f);
    createThread(f);
    createThread(f);

    ssp(1);

    // 实际测试下来很多次输出还是8000，哈哈哈
    SPDLOG_INFO("value[{}]", value);

    return 0;
}