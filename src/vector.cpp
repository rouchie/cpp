#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<uint32_t> v;

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    v.push_back(1);

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    v.reserve(20);

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    {
        // 表示20个元素，值都是0
        std::vector<uint32_t> v(20);
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        // 表示20个元素，值都是1024
        std::vector<uint32_t> v(20, 1024);
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        // 表示1个元素, 值是20
        std::vector<uint32_t> v{20};
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        std::vector<uint32_t> v(20, 1024);
        for (auto ii = v.begin(); ii < v.end(); ++ii) {
            SPDLOG_INFO("[{}]", *ii);
        }

        //对于容器来说自身带的begin/end函数跟std::begin/std::end函数没有区别
        //std::begin/std::end是c++11里添加的，可以使用在数组上
        for (auto ii = std::begin(v); ii < std::end(v); ++ii) {
            SPDLOG_INFO("[{}]", *ii);
        }

        const char name[] = "rouchie";        
        for (auto c = std::begin(name); c < std::end(name); ++c) {
            SPDLOG_INFO("[{}]", *c);
        }
    }

    return 0;
}