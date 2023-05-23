#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include "bigdog.h"

// 原型模式

// Prototype
// ConcretePrototype

class Prototype {
public:
    virtual ~Prototype() {}
    virtual Prototype * clone() = 0;

    void setId(uint32_t id) { m_id = id; }
    uint32_t getId() { return m_id; }

    void showId() {
        SPDLOG_DEBUG("id: {}", m_id);
    }

private:
    uint32_t m_id = 0;
};

class ConcretePrototype : public Prototype {
public:
    virtual ConcretePrototype * clone() override {
        ConcretePrototype * p = new ConcretePrototype;
        *p = *this;
        p->setId(this->getId()+1);

        return p;
    }
};

void test_prototype()
{
    std::shared_ptr<Prototype> c(new ConcretePrototype);
    std::shared_ptr<Prototype> d(c->clone());

    c->showId();
    d->showId();
}

#endif // PROTOTYPE_H
