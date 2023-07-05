#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v0 {3, 1, 2};
    std::vector<int> v1 {3, 1, 2};
    bool same = std::equal(std::begin(v0), std::end(v0), std::begin(v1), std::end(v1));

    SPDLOG_INFO("v0/v1 is same[{}]", same);

    // 求和
    auto sum = std::accumulate(v0.begin(), v0.end(), 0);
    SPDLOG_INFO("sum v0 [{}]", sum);

    // 乘积
    auto product = std::accumulate(v0.begin(), v0.end(), 1, std::multiplies<int>());
    SPDLOG_INFO("product v0 [{}]", product);

    product = std::accumulate(v0.begin(), v0.end(), 1, [](int total, int c) {
        return total * c;
    });
    SPDLOG_INFO("product v0 [{}]", product);

    std::vector<std::string> s{"hello", "world", "and fuck you"};

    auto w = std::accumulate(std::begin(s), std::end(s), std::string{});
    SPDLOG_INFO("word [{}]", w);

    return 0;
}