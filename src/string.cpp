#include "3rdparty.h"

int main()
{
    spdlog_init();

    {
        std::string s = "1024";
        uint32_t a = std::stoi(s);
        SPDLOG_INFO("{}", a);
    }

    {
        uint32_t a = 1024;
        double b = 1024.1024;
        std::string s0 = std::to_string(a);
        std::string s1 = std::to_string(b);

        SPDLOG_INFO("s0[{}] s1[{}]", s0, s1);
    }

    {
        const char * p = nullptr;
        std::string s = p;          // 用 nullptr 初始化一直以为会有一个默认值，其实会抛出异常
    }

    return 0;
}
