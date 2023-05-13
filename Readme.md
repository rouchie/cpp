# cpp11 特性

## constexpr

- constexpr 函数

C++11的constexpr函数有着比较多的限制：

1. 函数体只有单一的return返回语句
2. 函数必须返回值（不能是void函数）
3. 在使用前必须已有定义
4. return返回语句表达式中不能使用非常量表达式的函数、全局数据，且必须是一个常量表达式

C++14对constexpr函数的使用限制进行了放宽：

1. 可以使用局部变量和循环
2. 可以使用多个return

## final

- 修饰虚函数，阻止子类重写父类函数

- 修饰类，阻止类被继承

```cpp
class A {
    public:
        virtual void hello() {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        virtual void hello() final {
            SPDLOG_INFO("B hello");
        }
};

class C final : public B {
    public:
        // 重写的话，就会报错
        // virtual void hello() final { SPDLOG_INFO("A hello"); }
};

// class D : public C {
// 
// };
```

## override

override 关键字可以确保重写了虚函数，避免人为的写错函数

```cpp
class A {
    public:
        virtual void hello() {
            SPDLOG_INFO("A hello");
        }
};

class B : public A {
    public:
        virtual void hello() override {
            SPDLOG_INFO("B hello");
        }

        // 会报错
        // virtual void world() override() {
        //     SPDLOG_INFO("B world");
        // }
};
```

## template

c++11 里优化了两个模板相关的内容

1. 优化了右尖括号
2. 优化了函数模板的默认参数

```cpp
template <typename T = int>
class A {
    public:
        A(T t);
};

template <typename T>
A<T>::A(T t)
{
    SPDLOG_INFO("type T({}) {}", typeid(t).name(), t);
}

template <typename T = std::string>
void hello(T t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(t).name(), t);
}

A<int> a(1);
A<std::string> b("www.baidu.com");
A<> c(20);
// A c(20); 不可以这么使用，类必须带上尖括号

hello<int>(10);
hello<std::string>("hello world");
hello<>("www.bing.com");
hello("www.hello.com");
```

函数模板代表了一类函数，模板函数表示某一具体函数。

- 函数模板
提供了一类函数的抽象，它提供了任意类型为参数及返回值
- 模板函数
函数模板经实例化后生成的具体函数成为模板函数
