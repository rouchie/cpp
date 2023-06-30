#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v{1, 2, 3, 3, 1, 3, 10, 100};

    auto result = find(begin(v), end(v), 1);
    SPDLOG_INFO("find [{}]", *result);

    result = find(result, end(v), 1024);
    if (result != v.end()) SPDLOG_INFO("find [{}]", *result);

    // 查找第一个返回true的
    result = find_if(v.begin(), v.end(), [](auto elem) {return elem == 10;});
    if (result != v.end()) SPDLOG_INFO("find [{}]", *result);

    // 查找第一个返回false的
    result = find_if_not(v.begin(), v.end(), [](auto elem) {return elem == 10;});
    if (result != v.end()) SPDLOG_INFO("find not [{}]", *result);

    std::vector<int> primes {3, 10, 100};
    result = find_first_of(v.begin(), v.end(), primes.begin(), primes.end());
    if (result != v.end()) SPDLOG_INFO("find first [{}]", *result);

    // search、find_end 都是要子集匹配才算找到
    result = search(v.begin(), v.end(), primes.begin(), primes.end());
    SPDLOG_INFO("search [{}]", result == v.end() ? "failed" : "success");

    result = find_end(v.begin(), v.end(), primes.begin(), primes.end());
    SPDLOG_INFO("find_end distance [{}]", std::distance(v.begin(), result));

    // 连续2次出现3的位置
    result = search_n(v.begin(), v.end(), 2, 3);
    if (result != v.end()) SPDLOG_INFO("2 of {}", *result);

    // 返回第一个连续两次出现的元素
    result = std::adjacent_find(v.begin(), v.end());

    return 0;
}