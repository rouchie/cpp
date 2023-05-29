#include "3rdparty.h"

class A0 {
    public:
        A0(const A0 & a) = delete;
};

class A1 {
};

class A2 : public std::runtime_error {
    public:
        A2(std::string s) : std::runtime_error(s) {}

        virtual const char * what() const noexcept override {
            return "A2";

        }
};

// 函数声明了 noexcept，但里面又抛出异常，这种异常无法捕获，会导致程序终止
void hello() noexcept
{
    // 而且里面还有 warning
    throw std::logic_error{"hello"};
}

int main()
{
    spdlog_init();

    {
        // throw 可以抛出任何类型，但是不能抛出不能拷贝的类
        try {
            throw int{1024};
        } catch(int e) {
            SPDLOG_INFO("catch int [{}]", e);
        }
    }

    {
        // A0 不能拷贝，所以没法抛出
        // throw A0();
        try {
            throw A1{};
        } catch (const A1 & a) {
            SPDLOG_INFO("throw A1");
        }
    }

    {
        try {
            throw A2{"some"};
        } catch(const std::runtime_error & e) {
            SPDLOG_INFO("what [{}]", e.what());
        }

        try {
            throw std::runtime_error{"runtime error"};
        } catch(const std::exception & e) {
            SPDLOG_INFO("what [{}]", e.what());
        }
    }

    {
        try {
            throw std::logic_error{"logic error"};
        } catch(const std::exception & e) {
            SPDLOG_INFO("what [{}]", e.what());
        }
    }

    {
        try {
            hello();
        } catch(std::exception & e) {
            SPDLOG_INFO("这里不会捕获到异常，因为hello声明成了noexcept [{}]", e.what());
        }
    }

    return 0;
}