#include "3rdparty.h"

// override 关键字可以确保重写了虚函数，避免人为的写错函数

class A {
    public:
        virtual void hello() {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        virtual void hello() override {
            SPDLOG_INFO("B hello");
        }

        // virtual void world() override() {
        //     SPDLOG_INFO("B world");
        // }
};

int main()
{
    spdlog_init();

    std::shared_ptr<A> a(new B);
    a->hello();

    return 0;
}