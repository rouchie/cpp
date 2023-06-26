#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v {1, 2, 3, 2, 2, 10, 2, 10};

    {
        auto c = std::count(std::begin(v), std::end(v), 2);
        SPDLOG_INFO("count of 2 is [{}]", c);
    }

    {
        auto c = std::count(v.begin(), v.end(), 10);
        SPDLOG_INFO("count of 10 is [{}]", c);
    }
     
    {
        auto c = std::count_if(v.begin(), v.end(), [](auto elem) {
            return (elem == 2 || elem == 10);
        });
        SPDLOG_INFO("count of 2 and 10 is [{}]", c);
    }

    std::map<int, int> m {{1, 10}, {2, 20}, {3, 10}, {4, 10}};

    {
        auto c = std::count_if(m.begin(), m.end(), [](auto elem) {
            return elem.second == 10;
        });
        SPDLOG_INFO("count of 10 is [{}]", c);
    }

    {
        auto c = std::count_if(m.begin(), m.end(), [](std::pair<int, int> elem) {
            return elem.second == 10;
        });
        SPDLOG_INFO("count of 10 is [{}]", c);
    }

    {
        // all_of 判断是否全部都是 true
        auto c = std::all_of(m.begin(), m.end(), [](std::pair<int, int> elem) {
            return elem.second == 10;
        });
        SPDLOG_INFO("all of 10 is [{}]", c);
    }

    {
        // none_of 判断是否全部都是 false
        auto c = std::none_of(m.begin(), m.end(), [](std::pair<int, int> elem) {
            return elem.second == 10;
        });
        SPDLOG_INFO("none of 10 is [{}]", c);
    }

    {
        // any_of 判断是否有 true
        auto c = std::any_of(m.begin(), m.end(), [](std::pair<int, int> elem) {
            return elem.second == 10;
        });
        SPDLOG_INFO("any of 10 is [{}]", c);
    }


    return 0;
}