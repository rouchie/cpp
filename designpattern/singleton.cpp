#include "3rdparty.h"

class Singleton {
public:
    // 懒汉式，线程安全
    static Singleton * getInstance_01() {
        std::unique_lock<std::mutex> lock(mutex);

        if (!instance) {
            instance = new Singleton("getInstance_01");
        }

        return instance;
    }

    // 懒汉式，线程非安全
    static Singleton * getInstance_02() {
        if (!instance) instance = new Singleton("getInstance_02");
        return instance;
    }

    // 饿汉式，直接 Singleton* Singleton::instance = new Singleton;
    // 但也存在问题，虽然变量会在main函数之前实例化，但是也有可能会有其他调用了 getInstance_03 在变量实例化之前
    static Singleton * getInstance_03() {
        return instance;
    }

    // DCL，双检锁
    // DCL存在失效问题，java 需要 volatile 关键字，c++11 可以使用 atomic
    static Singleton * getInstance_04() {
        if (!instance) {
            std::unique_lock<std::mutex> lock(mutex);
            if (!instance) {
                instance = new Singleton("DCL");
            }
        }

        return instance;
    }

    // 此乃最优解, c++11 之后线程安全
    static Singleton * getInstance_05() {
        static Singleton instance("getInstance_05");
        return &instance;
    }

    void some(int i) {
        SPDLOG_DEBUG("singleton do some, {}", i);
    }

private:
    Singleton(const char *name) {
        SPDLOG_DEBUG("Singleton [{}]", name);
    }
    ~Singleton() {
        SPDLOG_DEBUG("~Singleton");
    }

    class SingletonDeletor {
        public:
        ~SingletonDeletor() {
            if (Singleton::instance) delete Singleton::instance;
        }
    };
    static SingletonDeletor deletor;

private:
    static Singleton * instance;
    static std::mutex mutex;
};

// Singleton* Singleton::instance = new Singleton; // 配合 getInstance_03 使用
Singleton* Singleton::instance = nullptr;
std::mutex Singleton::mutex;
Singleton::SingletonDeletor Singleton::deletor;

// 最好的单例模式，写法
class OtherSingleton {
public:
    ~OtherSingleton() {}
    static OtherSingleton * instance() {
#if 0 // 需要 new 出来的静态对象可以这样写
        static std::shared_ptr<OtherSingleton> one(new OtherSingleton);
        return one.get();
#else // 不需要 new 可以之间使用栈空间
        static OtherSingleton one;
        return &one;
#endif
    }
private:
    OtherSingleton() {}
};

inline void test_singleton()
{
    for (auto i=0; i<100; i++) {
        createThread([](int ii) {
            Singleton * instance = Singleton::getInstance_05();
            instance->some(ii);
        }, i);
    }
}

// 单例模式
// 1. 构造函数需要私有化
// 2. 拷贝构造和拷贝赋值需要delete

class Singleton0 {
    public:
        // 饿汉式单例模式
        // 它的特点是在程序启动时就创建单例对象，因此也被称为静态单例模式。
        static Singleton0 & getInstance0() {
            static Singleton0 ins;
            return ins;
        }

        // 懒汉式单例模式
        // 它的特点是在第一次使用时才创建单例对象，因此也被称为动态单例模式
        static Singleton0 & getInstance1() {
            static Singleton0 *pIns = new Singleton0;
            return *pIns;
        }

    private:
        Singleton0() {}
        Singleton0(const Singleton0&) = delete;
        Singleton0& operator=(const Singleton0&) = delete;
};

int main(int , char **)
{
    spdlog_init();

    test_singleton();

    return 0;
}