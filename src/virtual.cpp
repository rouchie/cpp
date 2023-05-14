#include "3rdparty.h"

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
    void *p;
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