#include "3rdparty.h"

#include <future>

class A {
    public:
        A(int v) : _v(v) {}

        int value() { return _v; }

    private:
        int _v;
};

std::shared_ptr<A> someWork()
{
    ssp(2);
    return std::make_shared<A>(456);
}

int main()
{
    spdlog_init();

    {
        std::promise<A> pro;
        auto f = pro.get_future();

        createThread([](std::promise<A> & p) {
            ssp(2);
            p.set_value(A(777));
        }, std::ref(pro));

        SPDLOG_INFO("promise [{}]", f.get().value());
    }

    {
        std::packaged_task<A(int)> task([](int) -> A { return A(1024); });

        auto f = task.get_future();

        createThread(std::move(task), 123);

        A a = f.get();
        SPDLOG_INFO("value [{}]", a.value());
    }

    {
        std::packaged_task<std::shared_ptr<A>()> task(someWork);

        auto f = task.get_future();

        createThread(std::move(task));

        auto shp = f.get();
        SPDLOG_INFO("value [{}]", shp->value());
    }

    return 0;
}