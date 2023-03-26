#include "3rdparty.h"

using INT = int;
using FUNC = void (*)(int, int);

// 很简单就能表达std::map了，这是typedef做不到的，如果typedef要做到这样需要结构体包装一次
template <typename T>
using MAP = std::map<int, T>;

class A {
    public:
        A(int i) : _i(i) {}
        void show() {
            SPDLOG_INFO("i[{}]", _i);
        }

    private:
        int _i = 0;
};

class B : public A {
    public:
        // 继承父类构造函数
        using A::A;

        // 引入父类函数
        using A::show;

        void show(int i) {
            SPDLOG_INFO("i[{}]", i);
        }
};

int main()
{
    spdlog_init();

    INT i = 0;

    SPDLOG_INFO("i[{}]", i);

    FUNC f = [](int, int) {};
    f(0, 0);

    MAP<std::string> m;
    m.insert(std::make_pair(1, "hello"));
    m.insert(std::make_pair(2, "world"));
    m.insert(std::make_pair(3, "ni"));
    m.insert(std::make_pair(3, "hao"));

    show(m);

    return 0;
}