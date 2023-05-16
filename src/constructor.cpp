#include "3rdparty.h"

// 委托构造需要注意的点
// 1. 不能形成环
// 2. 调用委托构造之后无法再在初始化列表中初始化其他成员

class A {
    public:
        A(int _a) : a(_a) {
            b = 0;
            c = 0;
        }

        // 委托构造函数
        A(int _a, int _b) : A(_a) {
            b = _b;
        }
        A(int _a, int _b, int _c) : A(_a, _b) {
            c = _c;
        }

        void show() {
            SPDLOG_INFO("a[{}] b[{}] c[{}]", a, b, c);
        }

    private:
        int a = 0;
        int b = 0;
        int c = 0;
};

class B : public A {
    public:
        // 在子类中使用父类中的构造函数
        using A::A;

        // 引入父类中的show，否在在子类中无法直接使用无参的show函数
        using A::show;
        void show(int i) {
            SPDLOG_INFO("i[{}]", i);
        }
};

class C {
    public:
        C(std::string s) : _s(s) {
            SPDLOG_INFO("C");
        }
        ~C() {
            SPDLOG_INFO("~C");
        }

        C(const C & c) {
            SPDLOG_INFO("const C &");
        }

        C(C && c) {
            SPDLOG_INFO("C &&");
        }

        C& operator=(const C & c) {
            SPDLOG_INFO("operator= const C &");
            return *this;
        }

        C& operator=(C && c) {
            SPDLOG_INFO("operator= C &&");
            this->_s = std::move(c._s);
            return *this;
        }

        void hello() {
            SPDLOG_INFO("hello[{}]", _s);
        }

    private:
        std::string _s;
};

int main()
{
    spdlog_init();

    C c("world");
    c = []() {
        C c("hello");
        c.hello();
        return c;
    }();

    c.hello();

    A a0(0);
    A a1(1, 2);
    A a2(2, 3, 4);

    B b0(0);
    B b1(1, 2);
    B b2(2, 3, 4);

    a0.show();
    a1.show();
    a2.show();

    b0.show();
    b1.show();
    b2.show();

    return 0;
}