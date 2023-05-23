#ifndef DECORATOR_H
#define DECORATOR_H

#include "bigdog.h"

// 装饰器（Decorator）模式的定义：指在不改变现有对象结构的情况下，动态地给该对象增加一些职责（即增加其额外功能）的模式，它属于对象结构型模式。
// 装饰器针对的是具体的对象
// 装饰器可以一层套一层
//     可以参考这么一个例子: 买汽车选配置，每一个装饰器就是增加一个配置，可以选择多个配置，价格也随之增加

// 四个部分组成，可以简化
// Component
// ConcreteComponent
// Decorator
// ConcreteDecorator

class BuyCat {
public:
    virtual ~BuyCat() {}
    virtual uint32_t price() = 0;
};

class BuyToyotaCat : public BuyCat {
public:
    virtual uint32_t price() override {
        return 120000;
    }
};

class MoreFunc : public BuyCat {
public:
    MoreFunc(BuyCat * cat) : m_cat(cat) {}
    ~MoreFunc() {
        delete m_cat;
    }
    virtual uint32_t price() override {
        return m_cat->price();
    }

private:
    BuyCat * m_cat;
};

class TianChuang : public MoreFunc {
public:
    TianChuang(BuyCat * cat) : MoreFunc(cat) {}
    virtual uint32_t price() override {
        return MoreFunc::price() + 10000;
    }
};

class SuperLunTai : public MoreFunc {
public:
    SuperLunTai(BuyCat * cat) : MoreFunc(cat) {}
    virtual uint32_t price() override {
        return MoreFunc::price() + 15000;
    }
};

void test_decorator()
{
    std::shared_ptr<BuyCat> cat = std::shared_ptr<BuyCat>(new SuperLunTai(new TianChuang(new BuyToyotaCat)));

    SPDLOG_DEBUG("price: {}", cat->price());
}

#endif // DECORATOR_H
