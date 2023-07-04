#include "3rdparty.h"

int main()
{
    spdlog_init();

    auto show = [](std::vector<int> & v) {
        for (auto & i : v) {
            SPDLOG_INFO("value[{}]", i);
        }
    };

    std::vector<int> v0 {0, 1, 2};
    std::vector<int> v1(v0.size());

    // 基本用法
    copy(std::begin(v0), std::end(v0), std::begin(v1));
    show(v1);
    
    // 更简单的拷贝
    std::vector<int> v2 = v0;
    show(v2);

    SPDLOG_INFO("-----------");

    std::vector<int> v3(v0.size());
    // 部分拷贝
    copy(std::begin(v0), std::begin(v0)+2, std::begin(v3));
    show(v3);

    return 0;
}