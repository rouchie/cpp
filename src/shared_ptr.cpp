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
    }
 
    {
        std::shared_ptr<A> shp = std::make_shared<A>();
        shp->hello();
    }

    return 0;
}