#include "3rdparty.h"

// final 修饰虚函数，阻止子类重写父类函数
// final 修饰类，阻止类被继承

class A {
    public:
        virtual void hello() {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        virtual void hello() final {
            SPDLOG_INFO("B hello");
        }
};

class C final : public B {
    public:
        // 重写的话，就会报错
        // virtual void hello() final { SPDLOG_INFO("A hello"); }
};

// class D : public C {
// 
// };

int main()
{
    spdlog_init();

    A * a = new C;
    a->hello();

    return 0;
}