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

// 另一种不能继承的写法，之前都不知道还能这么搞的
template<typename T>
class E {
    E() {}
    ~E() {}
public:
    friend T;
};

// 这样 F 就是一个不能被继承的类，所有虚拟继承自类E的类，都将是不能被继承的类
class F : public virtual E<F> {
public:
    void hello() {}
};

class G : public F {
};

int main()
{
    spdlog_init();

    A * a = new C;
    a->hello();

    // F * f = new G;

    return 0;
}