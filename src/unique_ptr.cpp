#include "3rdparty.h"

class A {
    public:
        A() {
            SPDLOG_INFO("A");
        }
        virtual ~A() {
            SPDLOG_INFO("~A");
        }
        virtual void hello() {
            SPDLOG_INFO("A hello");
        }
};

class A0 : public A {
    public:
        virtual void hello() override {
            SPDLOG_INFO("A0");
        }
};

class A1 : public A {
    public:
        virtual void hello() override {
            SPDLOG_INFO("A1");
        }
};

class A2 : public A {
    public:
        virtual void hello() override {
            SPDLOG_INFO("A2");
        }
};

std::unique_ptr<A> insA0(int type)
{
    std::unique_ptr<A> a(nullptr);

    switch (type) {
        case 0: {
            a.reset(new A0);
        } break;
        case 1: {
            a.reset(new A1);
        } break;
        case 2: {
            a.reset(new A2);
        } break;
    }

    return a;
}

void delA(A * a)
{
    a->hello();
    delete a;
}

class Deleter {
    public:
        void operator()(A* p) {
            SPDLOG_INFO("our Deleter");
            delete p;
        }
};

class Some {
    public:
    private:
        void *p;
        Deleter d;
};

// std::unique_ptr 不是线程安全

std::unique_ptr<A> u{nullptr};

int main()
{
    spdlog_init();
    
    // 肯定是会段错误的
    // u->hello();

    u = insA0(2);
    u->hello();

    std::unique_ptr<A> a;
    
    a = insA0(0);
    a->hello();
    
    a = insA0(1);
    a->hello();
    
    a = insA0(2);
    a->hello();

    SPDLOG_INFO("sizeof unique_ptr [{}]", sizeof(a));

    // std::unique_ptr 返回值可以直接赋值给 std::shared_ptr
    std::shared_ptr<A> shp = insA0(0);
    shp->hello();

    shp = std::move(a);
    shp->hello();

    SPDLOG_INFO("sizeof shared_ptr [{}]", sizeof(shp));

    // 会导致运行时错误
    // a->hello();

    auto f = [](A*p) {
        p->hello();
        delete p;
    };

    // std::unique_ptr 必须在定义变量时显示的指出删除器，如果需要的话，而std::shared_ptr则不需要
    std::unique_ptr<A, decltype(f)> a1(new A1, f);
    SPDLOG_INFO("sizeof unique_ptr [{}]", sizeof(a1));
    a1.reset();

    // 这里一定要注意，decltype(&delA) 必须加上 & 符号
    std::unique_ptr<A, decltype(&delA)> a2(new A2, delA);
    SPDLOG_INFO("sizeof unique_ptr [{}]", sizeof(a2));
    a2.reset();

    std::unique_ptr<A, void(*)(A*)> a3(new A1, delA);
    SPDLOG_INFO("sizeof unique_ptr [{}]", sizeof(a3));
    a3.reset();

    // 还可以指定一个类，里面仿函数
    std::unique_ptr<A, Deleter> a4(new A2);
    SPDLOG_INFO("sizeof unique_ptr [{}]", sizeof(a4));
    SPDLOG_INFO("sizeof Deleter [{}]", sizeof(Deleter));
    SPDLOG_INFO("sizeof Some [{}]", sizeof(Some));
    
    // unique_ptr 可以用在数组上，而shared_ptr不行
    // 1. shared_ptr 根本没定义 opeator[] 函数，而unique_ptr有
    // 2. unique_ptr 可以指定删除器，添加了删除器的unique_ptr和没添加删除器的unique_ptr就不是同一个类型了
    // 3. shared_ptr 不能自定义删除器，但可以在对象中添加删除器类来达到相同目的
    // 无法得知数组的大小
    std::unique_ptr<int[]> arr(new int[10]);
    std::shared_ptr<int[]> arr1(new int[10]);
    arr1.get()[0] = 10;

    for (int i=0; i<10; i++) {
        // 可以直接操作 []
        arr[i] = 1024;
    }

    return 0;
}