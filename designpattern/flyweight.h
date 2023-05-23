#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include "bigdog.h"

// 享元模式

// 四个组成部分
// Flyweight
// ConcreteFlyweight
// UnsharedFlyweight
// FlyweightFactory

class Shape {
public:

};

class IShape : public Shape {

};

class LShape : public Shape {

};

class ZShape : public Shape {

};

class OShape : public Shape {

};

class TShape : public Shape {

};

class SShape : public Shape {

};

class JShape : public Shape {

};

class ShapeFactory {
public:
    ShapeFactory() {
        m_shapes["I"] = new IShape;
        m_shapes["L"] = new LShape;
        m_shapes["Z"] = new ZShape;
        m_shapes["O"] = new OShape;
        m_shapes["T"] = new TShape;
        m_shapes["S"] = new SShape;
        m_shapes["J"] = new JShape;
    }

    Shape * getShape(std::string s) {
        auto it = m_shapes.find(s);

        if (it == m_shapes.end()) {
            it = m_shapes.find("O");
        }

        return it->second;
    }

private:
    std::map<std::string, Shape *> m_shapes;
};

#endif // FLYWEIGHT_H
