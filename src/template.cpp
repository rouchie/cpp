#include "3rdparty.h"

// c++11 对模板做了两个优化
// 1. 右尖括号的优化
// 2. 函数模板的默认参数

/*
- 函数模板
提供了一类函数的抽象，它提供了任意类型为参数及返回值
- 模板函数
函数模板经实例化后生成的具体函数称为模板函数
*/

template <typename T = int>
class A {
    public:
        A(T t);

        operator std::string() {
            return fmt::format("value {}", _t);
        }

        template<typename OStream>
        friend OStream &operator<<(OStream &os, const A &a) {
            return os << "value: [" << a._t << "]";
        }

    private:
        T _t;
};

template <typename T>
A<T>::A(T t) : _t(t)
{
    SPDLOG_INFO("type T({}) {}", typeid(t).name(), t);
}

template <typename T = std::string>
void hello(T t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(t).name(), t);
}

template <typename T0, typename T1>
T0& larger(T0 && a, T1 && b)
{
    SPDLOG_INFO("type a({}) b({})", typeid(a).name(), typeid(b).name());
    return a > b ? a : b;
}

// 模板类型推导

// 1. 引用或者指针
template <typename T>
void f1(T& t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(t).name(), t);
}

// 2. 通用引用
template <typename T>
void f2(T&& t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(T).name(), t);
}

// 3. 普通类型
template <typename T>
void f3(T t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(T).name(), t);
}

int main()
{
    spdlog_init();

    // 类型推导情况1，引用或者指针
    {
        int i = 10;
        const int j = 20;
        const int & k = j;

        f1(i);          // T -> int, t -> int &
        f1(j);           // T -> const int, t -> const int &
        f1(k);           // T -> const int, t -> const int &
        // 有一点需要注意，类型推导中，变量引用特性会忽略，所以用int变量调用和int&变量调用效果是一样的
    }

    // 类型推导情况2，通用引用，这并不是右值引用，虽然长的一样
    // 通用引用：要么是左值引用，要么是右值引用
    // 通用引用格式必须是 T&&，不能是 const T&&
    {
        // 如果参数是左值，则 T 为左值引用，这也是唯一一种 T 会被推导为引用的情况
        // 如果参数是右值，则 t 为右值引用，即 T 为普通类型
        int i = 10;
        const int j = 20;
        const int & k = j;
        auto && z = i;      // 需要推导的类型，则就不是看到的&&，可能是左值引用也可能是右值引用
        int && n = 20;

        f2(i);
        f2(j);
        f2(k);
        f2(30);
        f2(n);
        f2(z);

        // 可以用下面方式查看具体类型
        // TD<decltype(n)> td;
        // TD<decltype(z)> td;
    }

    // 类型推导情况3，通用类型，会忽略引用/const特性，并且生成一个拷贝
    {
        int i = 10;
        const int j = 20;
        const int & k = j;
        auto && z = i;      // 需要推导的类型，则就不是看到的&&，可能是左值引用也可能是右值引用
        int && n = 20;

        // 推导出来所有都是int类型
        f3(i);
        f3(j);
        f3(k);
        f3(30);
        f3(n);
        f3(z);
    }

    larger<double>(3, 2.5);

    int i = 2;
    larger(1, i); // 打印出来类型都是int，但其实应该是int，int&类型

    A<int> a(1);
    A<std::string> b("www.baidu.com");
    A<> c(20);

    // A c(20); 不可以这么使用，类必须带上尖括号，函数模板则可以不带

    hello<int>(10);
    hello<std::string>("hello world");
    hello<const char *>("www.bing.com");
    hello<>("www.bing.com");                // 推导出来的是 const char *
    hello("www.hello.com");                 // 推导出来的是 const char *

    // SPDLOG_INFO("{}", new A<int>(10));

    return 0;
}