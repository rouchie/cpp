#ifndef TEMPLATEMOTHOD_H
#define TEMPLATEMOTHOD_H

#include "bigdog.h"

// 模板方法模式：这个就是自己平时也经常在用的，比较简单的一个模式，QThread 就是使用这个模式

class RThread : public std::enable_shared_from_this<RThread> {
public:
    virtual ~RThread() {}
    void start() {
        started(true);
        createThread([](std::shared_ptr<RThread> thread) {
            thread->run();
            thread->started(false);
        }, this->shared_from_this());
    }

    virtual void run() = 0;

    void started(bool f) {
        m_started = f;
    }

private:
    bool m_started = false;
};

class SubThread : public RThread {
public:
    void run() override {
        for (int i=0; i<5; i++) {
            SPDLOG_DEBUG("running... {}", i);
            ssp(1);
        }
    }
};

void test_templatemothod()
{
    std::shared_ptr<RThread> thread(new SubThread);
    thread->start();
}

#endif // TEMPLATEMOTHOD_H
