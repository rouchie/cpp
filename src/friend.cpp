#include "3rdparty.h"

// 友元函数公有私有目前没发现有什么区别

class A {
    public:
        // 使用普通函数作为友元函数
        friend void f0(A& a);

    private:
        friend void f1(A& a);

        // 模板函数作为友元函数
        template<typename T>
        friend void f2(T && t);
    
    public:
        void hello() {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        void hello();
        void world();
};

void B::hello()
{
    f0(*this);
}

void B::world()
{
    f1(*this);
}

void f0(A& a)
{
    SPDLOG_INFO("f0");
}

void f1(A& a)
{
    SPDLOG_INFO("f1");
}

template <typename T>
void f2(T && t)
{
    t.hello();
}

class D;
class E;

class C {
    public:
        void hello(D& d, E& e);
        void world(E& e);
};

class D {
    // 使用其他类的成员函数作为友元函数
    friend void C::hello(D& d, E& e);

    private:
        int d = 0;
};

class E {
    // 友元类
    friend class C;

    private:
        int e = 0;
};

void C::hello(D& d, E& e)
{
    d.d = 1024;
    e.e = 100;
}

void C::world(E& e)
{
    e.e = 1024;
}

int main()
{
    spdlog_init();

    A a;

    f0(a);
    f1(a);

    f2(a);

    B b;
    b.hello();
    b.world();

    C c;
    D d;
    E e;

    c.hello(d, e);

    return 0;
}
