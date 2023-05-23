#ifndef BRIDGE_H
#define BRIDGE_H

#include "bigdog.h"

// 桥接模式

// 四个角色
// Abstraction
// Refined Abstraction
// Implementor
// Concrete Implementor

class Implementor {
public:
    virtual ~Implementor() {}
    virtual void some() = 0;
};

class ConcreteImplementor : public Implementor {
public:
    void some() override {
        SPDLOG_DEBUG("ConcreteImplementor");
    }
};

class Abstraction {
public:
    Abstraction(Implementor * imp) : m_imp(imp) {}
    virtual ~Abstraction() {
        delete m_imp;
    }

    void some() {
        m_imp->some();
    }

private:
    Implementor * m_imp;
};

class RefinedAbstraction : public Abstraction {
public:
    RefinedAbstraction(Implementor * imp) : Abstraction(imp) {}
};

// 一个实例
class Color {
public:
    Color() {}
    virtual ~Color() {}
    virtual std::string color() = 0;
};

class Red : public Color {
public:
    std::string color() override {
        return "red";
    }
};

class Blue : public Color {
public:
    std::string color() override {
        return "blue";
    }
};

class Animal {
public:
    Animal(Color * color) : m_color(color) {}
    void show() {
        SPDLOG_DEBUG("color: {}", m_color->color());
    }

    virtual ~Animal() {}

private:
    Color * m_color;
};

class Dog : public Animal {
public:
    Dog(Color * color) : Animal(color) {}
};

class Cat : public Animal {
public:
    Cat(Color * color) : Animal(color) {}
};

void test_bridge()
{
    std::shared_ptr<Abstraction> a(new RefinedAbstraction(new ConcreteImplementor));
    a->some();

    std::shared_ptr<Animal> dog0(new Dog(new Red));
    std::shared_ptr<Animal> dog1(new Dog(new Blue));
    std::shared_ptr<Animal> cat(new Cat(new Blue));

    dog0->show();
    dog1->show();
    cat->show();
}

#endif // BRIDGE_H
