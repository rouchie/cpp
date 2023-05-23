#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "bigdog.h"

// 中介者模式：定义一个中介对象来封装一系列对象之间的交互，使原有对象之间的耦合松散，且可以独立地改变它们之间的交互。中介者模式又叫调停模式，它是迪米特法则的典型应用

// 四个组成部分
// Mediator
// ConcreteMediator
// Colleague
// ConcreteColleague

// 中介者模式主要是多对象之间解耦

class Mediator;

class Customer {
public:
    virtual ~Customer() {}
    virtual void send(std::string info) = 0;
    virtual void some(std::string info) = 0;

    void setMediator(Mediator * m) {
        m_mediator = m;
    }

protected:
    Mediator * m_mediator;
};

class Mediator {
public:
    virtual ~Mediator() {}
    void add(Customer * c) {
        c->setMediator(this);
        m_list.push_back(c);
    }

    virtual void reply(Customer * c, std::string info) = 0;

protected:
    std::list<Customer *> m_list;
};

class Seller : public Customer {
public:
    virtual void some(std::string info) override {
        SPDLOG_DEBUG("Seller: {}", info);
    }

    virtual void send(std::string info) override {
        std::string s = "somebody sell/" + info;
        m_mediator->reply(this, s);
    }
};

class Buyer : public Customer {
public:
    virtual void some(std::string info) override {
        SPDLOG_DEBUG("Buyer: {}", info);
    }

    virtual void send(std::string info) override {
        std::string s = "you can buy/" + info;
        m_mediator->reply(this, s);
    }
};

class ConcreteMediator : public Mediator {
public:
    virtual void reply(Customer *c, std::string info) override {
        for(auto it : m_list) {
            if (c != it) {
                c->some(info);
            }
        }
    }
};

void test_mediator()
{
    std::shared_ptr<Mediator> mediator(new ConcreteMediator);
    std::shared_ptr<Customer> c0(new Seller);
    std::shared_ptr<Customer> c1(new Buyer);
    std::shared_ptr<Customer> c2(new Buyer);
    std::shared_ptr<Customer> c3(new Seller);

    mediator->add(c0.get());
    mediator->add(c1.get());
    mediator->add(c2.get());
    mediator->add(c3.get());

    c0->send("903");
    c1->send("803");
}

#endif // MEDIATOR_H
