#ifndef ADAPTER_H
#define ADAPTER_H

#include "bigdog.h"

// 适配者模式: 无非就是将一组接口改为另一组接口的中间件

// 由三个角色
// Target   : 目标接口
// Adaptee  : 原始接口
// Adapter  : 适配器，原始接口 -> 目标接口

// 适配器模式（Adapter）通常适用于以下场景。
// 以前开发的系统存在满足新系统功能需求的类，但其接口同新系统的接口不一致。
// 使用第三方提供的组件，但组件接口定义和自己要求的接口定义不同。

class Target {
public:
    virtual ~Target() {}
    virtual void request() = 0;
};

class Adaptee {
public:
    void someapi() {
        SPDLOG_DEBUG("adaptee api");
    }
};

// 这里可以采用多重继承，也可以采用继承 Target 然后包含 Adaptee 成员
// 两种方式分别成为 类适配器 和 对象适配器
class Adapter : public Target , public Adaptee {
public:
    virtual void request() override {
        someapi();
    }
};

// 这里可以有多个 适配者 类，然后多个适配器类，然后有一个适配器基类，所有适配器类继承自基类

void test_adapter()
{
    std::shared_ptr<Target> p(new Adapter);

    p->request();
}

#endif // ADAPTER_H
