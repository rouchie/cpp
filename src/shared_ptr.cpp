#include "3rdparty.h"

class A {
    public:
        A() {
            SPDLOG_INFO("A");
        }
        ~A() {
            SPDLOG_INFO("~A");
        }

        void hello() {
            SPDLOG_INFO("hello");
        }
};

// 两点需要注意：
// 1. 如果要返回 std::shared_ptr<T>，则必须继承 enable_shared_from_this，而且必须是public继承，否则运行报错
// 2. 继承了 enable_shared_from_this 的类必须被 std::shared_ptr 管理
class B : public std::enable_shared_from_this<B> {
    public:
        std::shared_ptr<B> hello() {
            return shared_from_this();
        }
};

// 继承了 enable_shared_from_this，更常见的作法，通过静态函数获取 std::shared_ptr，则保证了不私自定义类
class C : public std::enable_shared_from_this<C> {
    public:
        static std::shared_ptr<C> instance() {
            return std::shared_ptr<C>();
        }

        std::shared_ptr<C> hello() {
            return shared_from_this();
        }

    private:
        C() {}
};

int main()
{
    spdlog_init();

    {
        std::shared_ptr<int> shp(new int{1024});
        SPDLOG_INFO("value[{}]", *shp.get());
    }

    {
        std::shared_ptr<A> shp(new A);
        shp->hello();
        SPDLOG_INFO("sizeof shared_ptr [{}]", sizeof(shp));
    }
 
    {
        std::shared_ptr<A> shp = std::make_shared<A>();
        shp->hello();
    }

    {
        std::shared_ptr<B> b0;
        std::shared_ptr<B> b1 = b0->hello();
    }

    return 0;
}