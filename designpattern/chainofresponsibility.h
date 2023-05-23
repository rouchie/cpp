#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H

#include "bigdog.h"

// 责任链模式

// 三个组成部分
// Handler
// ConcreteHandler
// Client

class Handler {
protected:
    std::shared_ptr<Handler> next{nullptr};

public:
    void setNext(std::shared_ptr<Handler> handle) {
        next = handle;
    }

    virtual bool handleRequest(int d, std::string s) = 0;
};

class Leader : public Handler {
public:
    bool handleRequest(int d, std::string s) {
        if (d < 2) {
            SPDLOG_DEBUG("Leader handle {}", s);
            return true;
        }

        return next->handleRequest(d, s);
    }
};

class PM : public Handler {
public:
    bool handleRequest(int d, std::string s) {
        if (d < 5) {
            SPDLOG_DEBUG("PM handle {}", s);
            return true;
        }

        return next->handleRequest(d, s);
    }
};

class Boss : public Handler {
public:
    bool handleRequest(int d, std::string s) {
        if (d > 10) return false;

        SPDLOG_DEBUG("Boss handle {}", s);
        return true;
    }
};

void test_chainofresponsibility()
{
    std::shared_ptr<Handler> leader(new Leader);
    std::shared_ptr<Handler> pm(new PM);
    std::shared_ptr<Handler> boss(new Boss);

    leader->setNext(pm);
    pm->setNext(boss);

    leader->handleRequest(1, "1 day");
    leader->handleRequest(3, "3 day");
    leader->handleRequest(6, "6 day");
}

#endif // CHAINOFRESPONSIBILITY_H
