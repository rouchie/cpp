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

    return 0;
}