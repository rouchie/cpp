#ifndef OBSERVER_H
#define OBSERVER_H

#include "bigdog.h"

// 观察者模式：订阅发布者模式，模型视图模式，

// 4 个组成部分
// Subject
// ConcreteSubject
// Observer
// ConcreteObserver

namespace OBSERVER {

class Observer;

class Subject {
public:
    virtual ~Subject() {}

    virtual void notify() = 0;

    void add(Observer * o) {
        m_list.push_back(o);
    }

protected:
    std::list<Observer *> m_list;
};

class Observer {
public:
    Observer(Subject * s) {
        s->add(this);
    }
    virtual ~Observer() {}
    virtual void some() = 0;
};

class ConcreteObserver0 : public Observer {
public:
    ConcreteObserver0(Subject * s) : Observer(s) {}

    void some() override {
        SPDLOG_DEBUG("000");
    }
};

class ConcreteObserver1 : public Observer {
public:
    ConcreteObserver1(Subject * s) : Observer(s) {}

    void some() override {
        SPDLOG_DEBUG("111");
    }
};

class ConcreteObserver2 : public Observer {
public:
    ConcreteObserver2(Subject * s) : Observer(s) {}

    void some() override {
        SPDLOG_DEBUG("222");
    }
};

class ConcreteSubject : public Subject {
public:
    void notify() override {
        for(auto it : m_list) {
            it->some();
        }
    }
};

};

void test_observer()
{
    using namespace OBSERVER;

    Subject * subject = new ConcreteSubject;
    new ConcreteObserver0(subject);
    new ConcreteObserver1(subject);
    new ConcreteObserver2(subject);

    subject->notify();
}

#endif // OBSERVER_H
