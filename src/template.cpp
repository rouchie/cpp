#include "3rdparty.h"

// c++11 对模板做了两个优化
// 1. 右尖括号的优化
// 2. 函数模板的默认参数

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

int main()
{
    spdlog_init();

    A<int> a(1);
    A<std::string> b("www.baidu.com");
    A<> c(20);
    // A c(20); 不可以这么使用，类必须带上尖括号

    hello<int>(10);
    hello<std::string>("hello world");
    hello<>("www.bing.com");
    hello("www.hello.com");

    // SPDLOG_INFO("{}", new A<int>(10));

    return 0;
}