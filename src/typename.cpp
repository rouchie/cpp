#include "3rdparty.h"

// 下面两处出现 typename
// 1. 模板
// 2. 第2处用法比较有意思，用来定义模板内的类型别名，T类型不确定，所以使用关键字 typename 告诉编译器这是一个类型而不是一个变量或者函数
template<typename T>
struct A {
    // 这里使用了 T::value_type，所以实例化模板时指定的类型T，必须有定义了 value_type，不然会编译报错
    typedef typename T::value_type value_type;
    typename T::value_type hello;
    value_type world;
};

struct B {
    typedef int value_type;
};

int main()
{
    spdlog_init();

    A<B> a;
    A<B>::value_type v;

    // TD<decltype(a.hello)> h;
    // TD<decltype(a.world)> w;

    return 0;
}