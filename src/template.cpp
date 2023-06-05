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

// 变长模板写法
template <typename T, typename ...A>
void makeThread(T && f, A && ... a) {
    SPDLOG_INFO("sizeof [{}]", sizeof...(a));
    std::thread(std::forward<T>(f), std::forward<A>(a)...).detach();
}

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
T f2(T&& t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(T).name(), t);
    // TD<decltype(t)> td;
    return t;
}

// 3. 普通类型
template <typename T>
void f3(T t)
{
    SPDLOG_INFO("hello type T({}) {}", typeid(T).name(), t);
    // TD<decltype(t)> td;
}

template <typename T>
void f4()
{
    // c++14才支持
    // template<typename _Tp>
    // using remove_reference_t = typename remove_reference<_Tp>::type;

    std::remove_reference_t<T> a{};
    a = a + a;

    // TD<decltype(a)> td;
    // TD<T> td;
}

// 奇怪的写法，
template <typename ... T>
void wrapper(T... t) {}

template <typename T>
T pr(T t)
{
    std::cout << t;
    return t;
}

template <typename ... T>
void world(T... t)
{
    SPDLOG_INFO("sizeof...t[{}]", sizeof...(t));
    wrapper(pr(t)...);
}

// 还可以这样写，模板参数非类型
template<int... v>
class C{};

template <typename T0, typename T1>
class D {

};

template <typename... T>
class E : private D<T...> {
    public:
        void hello() {}
};

// 非类型模板，递归
template <long ... nums>
struct M;

template <long first, long ... last>
struct M<first, last...> {
    static const long val = first * M<last...>::val;
};

template<>
struct M<> {
    static const long val = 1;
};

// 模板和数组的引用
// int &a[N]        a是一个数组，数组内容是引用
// int (&a)[N]      a是一个引用，引用的是一个int[N]的数组
template <typename T, size_t N>
size_t f5(T (&a)[N])
{
    // 用来计算字符串的大小，好像很不错
    return N;
}

int main()
{
    spdlog_init();

    {
        char w[] = "world";

        SPDLOG_INFO("len hello [{}]", f5("hello"));
        SPDLOG_INFO("len({}) [{}]", w, f5(w));

        const char (&a)[6] = "world";
        f5(a);
    }

    {
        // 不知道为什么编译报错了，书上明明就是这样写的
        // SPDLOG_INFO("Multiply<1, 2, 3> = {}", M<1, 2, 3>::val);
        // SPDLOG_INFO("Multiply<> = {}", M<>::val);
    }

    {
        world(1, 2.3, "hello", 45);

        C<1, 2, 3> c0;
        C<1, 2, 3> c1 = c0;
        c0 = c1;

        E<int, std::string> e;
        e.hello();
    }

    {
        int a = 10;
        int & b = a;
        f4<decltype(b)>();
    }

    {
        int i = 10;
        int && j = std::move(i);

        SPDLOG_INFO("i[{}] j[{}]", i, j);
    }

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
        int && n = 20;             // 这个到底意味着什么

        n+=1;

        f2<std::string>("world");       // std::string &&
        f2("hello");                    // const char (&)[6]
        f2(z);                         // int &
        f2(30);                         // int &&
        f2(k);                          // const int &
        f2(i);                         // int &
        f2(n);                         // int &
        f2(j);                          // const int &

        // 可以看到 f2("hello") 类型被推导为 const char (&)[6]，数组引用

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

    {
        auto k = larger<double>(3, 2.5);
        SPDLOG_INFO("k[{}]", k);

        // 下面这样的写法竟然是可以的，larger 返回了一个引用，因为n大，所以其实就是返回n本身，如果n小，则返回一个临时变量的引用
        int n = 20;
        larger(n, 2) = 10;
        SPDLOG_INFO("n[{}]", n);

        int i = 2;
        larger(1, i); // 打印出来类型都是int，但其实应该是int，int&类型
    }

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