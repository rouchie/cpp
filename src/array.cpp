#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::array<int32_t, 10> a0;
    std::array<int32_t, 20> a1{};
    a1.at(0) = 123;

    a0.fill(1024);

    // at 和 [] 都能访问容器，但是[]性能比at高，at每次都会检查是否越界，[]不做越界检查就是为了性能
    SPDLOG_INFO("{}-{}", a0.at(0), a0[1]);

    // 会抛出异常
    // a0.at(1024);

    SPDLOG_INFO("size[{}]", a0.size());

    int32_t total{};
    for (auto && v : a0) {
        total += v;
    }
    SPDLOG_INFO("total[{}]", total);

    // std::get 辅助函数，可以在编译时检查越界
    // SPDLOG_INFO("{}", std::get<10>(a0));
    SPDLOG_INFO("{}", std::get<1>(a0));

    auto begin = std::begin(a0);
    auto end = std::begin(a0);

    for (auto &ii = begin; ii < end; ii++) {
        ii += rand();
    }

    for (auto && v : a0) {
        SPDLOG_INFO("[{}]", v);
    }

    return 0;
}