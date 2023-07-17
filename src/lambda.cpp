#include "3rdparty.h"

// [capture](parameters) mutable -> return-type { statement }
// 1. 引用捕获可能导致悬挂引用
// 2. lambda 只能捕获作用域内可见的非静态局部变量

std::function<void(int)> f0()
{
    int i = 1024;

    // 1. 引用捕获可能导致悬挂引用
    // 这里使用了i的引用，会导致问题，因为函数都已经结束，返回了lambda，后续再调用这个lambda函数的话，会用到i变量，但是i已经释放了
    auto f = [&i](int j) {
        SPDLOG_INFO("i[{}] j[{}]", i, j);
    };

    return f;
}

std::function<void(int)> f1()
{
    int i = 1024;

    // 按值传递则没有这个问题'引用捕获可能导致悬挂引用'
    auto f = [i](int j) {
        SPDLOG_INFO("i[{}] j[{}]", i, j);
    };

    return f;
}

class A {
    public:
        void hello() {
            [=]() {
                // 这里为什么能捕获age呢？
                // 是因为每个成员函数默认有一个this，这里的=捕获的是this，而不是age
                SPDLOG_INFO("age[{]}]", age);
            }();
        }

    private:
        int age = 40;
};

// 匿名函数可以在模板中使用，并且还是递归
template <typename T>
void hello()
{
    std::function<T (T)> f = [&](T t) {
        if (t == 0) return 0;
        return t+f(t-1);
    };

    SPDLOG_INFO("0 加到 100 等于 [{}]", f(100));
    SPDLOG_INFO("0 加到 1000 等于 [{}]", f(1000));
    SPDLOG_INFO("0 加到 10000 等于 [{}]", f(10000));
}

int main()
{
    spdlog_init();

    hello<int>();

    // [](){} 其中的()都可以省略
    []{
        SPDLOG_INFO("省略()");
    }();

    // 有mutable关键字时，不可以省略()
    []() mutable {}();

    f0()(123);
    f1()(123);

    [n = 1+10*20]() {
        SPDLOG_INFO("c++14里可以这样捕获n[{}]", n);
    }();

    return 0;
}