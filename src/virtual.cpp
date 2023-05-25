#include "3rdparty.h"

//虚函数是怎么实现多态的，是有一个虚函数表，每个虚函数会在这个虚函数表指向的函数指针数组中
//子类实现虚函数之后，会覆盖掉虚函数表指向的数组相应位置
//这个时候怎么直接调用父类虚函数呢，只能通过类名来强制调用，这时候不是通过虚函数表来找了，而是直接去函数区根据相应地址找

class A {
    public:
        virtual void hello(int i) {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        int hello(int i, int j) {
            SPDLOG_INFO("B hello");
            return 0;
        }

        void hello(float i) {
            SPDLOG_INFO("B hello float");
        }

        // 报错
        // int hello(int i) {
        //     SPDLOG_INFO("B hello");
        // }
};

class C {

};

class D {
    void *p = nullptr;
};

int main()
{
    spdlog_init();

    A *a = new B;
    B *b = new B;

    a->hello(10);
    b->hello(10.);

    SPDLOG_INFO("size A [{}]", sizeof(A));
    SPDLOG_INFO("size B [{}]", sizeof(B));
    SPDLOG_INFO("size C [{}]", sizeof(C));
    SPDLOG_INFO("size D [{}]", sizeof(D));

    return 0;
}