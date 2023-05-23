#include "3rdparty.h"

// weak_ptr 三种用处
// 1. 缓存一些耗时的类
// 2. 观察者模式
// 3. A、B两个类互相包含对方的std::shared_ptr，会导致内存泄漏无法释放问题，所以其中一个需要改成std::weak_ptr

/*
对可能悬挂（dangle）的 std::shared_ptr-like 指针使用 std::weak_ptr。
std::weak_ptr 的潜在应用场景包括缓存、观察者列表以及防止std::shared_ptr环。
*/

class A {};

// 1. 缓存一些耗时的类
std::shared_ptr<A> LoadSome(uint32_t id)
{
    static std::unordered_map<uint32_t, std::weak_ptr<A>> um;

    auto ptr = um[id];
    auto shp = ptr.lock();
    if (!shp) {
        shp = std::make_shared<A>();
        um[id] = shp;
    }

    return shp;
}

// 2. 观察者模式
// 一个主题包含多个观察者，主题可以通过weak_ptr判断每个观察者是否可用

class C;
// 3. A、B两个类互相包含对方的std::shared_ptr，会导致内存泄漏无法释放问题，所以其中一个需要改成std::weak_ptr
class B {
    public:
        ~B() {
            SPDLOG_INFO("~B");
        }
        std::shared_ptr<C> c;
};

class C {
    public:
        ~C() {
            SPDLOG_INFO("~C");
        }
        std::weak_ptr<B> b;
        // 如果使用std::shared_ptr,则无法释放将导致内存泄漏
        // std::shared_ptr<B> b;
};

int main()
{
    spdlog_init();

    std::shared_ptr<B> b = std::make_shared<B>();
    std::shared_ptr<C> c = std::make_shared<C>();
    b->c = c;
    c->b = b;

    return 0;
}