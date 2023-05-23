#ifndef STRATEGY_H
#define STRATEGY_H

#include "sort.h"
#include "bigdog.h"

// 策略模式：和工厂模式非常的像，uml是一样的，但工厂模式属于创建型模式，要是的创建目标，而策略模式则是行为的封装，要的是不同的子类实现不同的算法

// 三个组成部分
// Strategy
// ConcreteStrategy
// Context

// 实现排序的算法可以用策略模式来写

class Context {
public:
    template<typename T>
    void sort(std::shared_ptr<Sort<T>> s, T * a, size_t n) {
        s->sort(a, n);
    }
};

void test_strategy()
{
    int a[] = {1, 100, 44, 20, 55};
    int b[] = {1, 100, 44, 20, 55};

    quick(a);

    auto s = new Quick<int>();
    s->sort(a, sizeof (a)/sizeof(a[0]));

    delete s;

    show(a);

    Context c;
    std::shared_ptr<Sort<int>> ss(new Quick<int>);
    c.sort(ss, b, sizeof(b)/sizeof(b[0]));

    show(b);
}

#endif // STRATEGY_H
