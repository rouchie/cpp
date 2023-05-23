#ifndef PROXY_H
#define PROXY_H

#include "bigdog.h"

class Subject;
void justSleep(std::shared_ptr<Subject> m_subject);

// 代理模式:
//     代理模式和适配者模式是不一样的，有时会比较模糊，代理是接口完全相同的，也就是继承自同一基类并且包含了要被代理的类，接口是完全一样的
//     适配器模式则是为了使用新接口代替老接口

// 包含三个部分
// Subject
// RealSubject
// Proxy

// 这个模式目前我能想到的一个用处是 RealSubject 需要做一件比较耗时的任务，采用代理类可以直接创建一个线程让起跑
// 我又想到了一个使用代理模式的例子，就是live555里 FrameFilter 类，应该算是代理类

class Subject : public std::enable_shared_from_this<Subject> {
public:
    Subject(std::string name) : m_name(name) {}
    virtual ~Subject() {
        SPDLOG_DEBUG("delete {}", m_name);
    }

    virtual void show() = 0;
    void setStatus(uint32_t status) {
        SPDLOG_DEBUG("status: {}", status);
    }

private:
    std::string m_name;
};

class RealSubject : public Subject {
public:
    RealSubject() : Subject("RealSubject") {}

    virtual void show() override {
        justSleep(this->shared_from_this());
        SPDLOG_DEBUG("Real Subject Show");
    }
};

class Proxy : public Subject {
public:
    Proxy() : Subject("Proxy"), m_subject(new RealSubject) {}

    virtual void show() override {
        createThread([](std::shared_ptr<Subject> subject) {
            subject->show();
        }, m_subject.get()->shared_from_this()); // 这里只是故意这么写，其实只要传入 m_subject 即可
    }

private:
    std::shared_ptr<Subject> m_subject;
};

void justSleep(std::shared_ptr<Subject> m_subject)
{
    ssp(2);
    m_subject->setStatus(rand()%5);
}

void test_proxy()
{
    std::shared_ptr<Subject> subject(new Proxy);
    subject->show();
}

#endif // PROXY_H
