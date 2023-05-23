#ifndef FACADE_H
#define FACADE_H

#include "bigdog.h"

// 外观模式: 感觉没什么用，就是一些列的类，通过一个总类来调用

// 三个组成部分
// Facade
// SubSystem
// Client

class SubSystem0 {
public:
    void func() {
        SPDLOG_DEBUG("sub system 0");
    }
};

class SubSystem1 {
public:
    void func() {
        SPDLOG_DEBUG("sub system 1");
    }
};

class SubSystem2 {
public:
    void func() {
        SPDLOG_DEBUG("sub system 2");
    }
};

class Facade {
public:
    void some() {
        ss0.func();
        ss1.func();
        ss2.func();
    }

private:
    SubSystem0 ss0;
    SubSystem1 ss1;
    SubSystem2 ss2;
};

void test_facade()
{
    Facade f;
    f.some();
}

#endif // FACADE_H
