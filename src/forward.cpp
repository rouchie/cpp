#include "3rdparty.h"

// 完美转发

// 不完美的情况
// 1. {} 初始化的内容无法推导为 initializer_list
// 2. 0/NULL无法推导为空指针，需要使用nullptr
// 3. 类的const static变量，不细说，好复杂
// 4. 重载的函数
// 5. 位字段

void f(int)
{
    SPDLOG_INFO("f0");
}

void f(int, int)
{
    SPDLOG_INFO("f1");
}

template <typename T, typename ...A>
void makeThread(T && f, A && ... a) {
    SPDLOG_INFO("sizeof [{}]", sizeof...(a));
    std::thread(std::forward<T>(f), std::forward<A>(a)...).detach();
}

template <typename T>
void T0(T t)
{
    SPDLOG_INFO("T0");
}

int main()
{
    spdlog_init();

    makeThread([](int i) {
        SPDLOG_INFO("i[{}]", i);
    }, 1024);

    // 完美转发的不完美，下面编译会报错，无法把{}推导为initializer_list
    // makeThread([](std::vector<int> v) {
    //     SPDLOG_INFO("v size[{}]", v.size());
    // }, {1, 2, 3});

    // 可以明确指定为initializer_list
    makeThread([](std::vector<int> v) {
        SPDLOG_INFO("v size[{}]", v.size());
    }, std::initializer_list<int>{1, 2, 3});

    // 完美转发的不完美，不要试图用0或者NULL来通过通用引用传递给指针
    // 使用0、NULL都会导致编译报错，使用nullptr则可以
    makeThread([](int *p) {
        if (p) SPDLOG_INFO("*p[{}]", *p);
    }, nullptr);

    // 重载函数无法直接传递
    // makeThread([](void func(int)) {
    //     func(0);
    // }, f);

    // 可以使用这个办法传递重载的函数
    using FUNC = void (*)(int);
    FUNC fk = f;

    makeThread([](void func(int)) {
        func(0);
    }, fk);

    // 函数模板传递的方式
    makeThread([](void func(int)) {
        func(0);
    }, static_cast<FUNC>(T0));

    ssp(1);

    return 0;
}