#include "3rdparty.h"

// 支持 sort 的容器，vector/list/deque/array
// map/set系列不支持sort函数

// 没有定义 operator< 函数，不能直接调用sort函数，但是调用sort时可以直接定义cmp函数
struct Hello {
    int a;
    std::string b;
};

int main()
{
    spdlog_init();

    {
        // 只有list容器有sort成员函数，使用的是归并排序，和std::stable_sort使用相同的算法
        std::list<int> l {1, 2, 10, 5, 4, 3};
        l.sort();
    }

    auto show = [](std::vector<int> v) {
        for (auto & i : v) {
            SPDLOG_INFO("value [{}]", i);
        }
    };

    std::vector<int> v {1, -10, 10, -100, 2, 5, 3, 100, 200};

    {
        // 会段错误
        // sort(v.begin()+2, v.begin());
        // show(v);
    }

    // 判断是否已经排序
    auto sorted = std::is_sorted(v.begin(), v.end());
    SPDLOG_INFO("sorted[{}]", sorted);

    sort(v.begin(), v.end());
    show(v);

    sort(v.begin(), v.end(), [](int elem0, int elem1) { return elem0 > elem1;});
    show(v);

    sort(v.begin(), v.end(), [](int elem0, int elem1) { return elem0 < elem1;});
    show(v);

    sort(v.begin(), v.end(), [](int elem0, int elem1) { return abs(elem0) < abs(elem1);});
    show(v);

    std::vector<Hello> hello {{5, "hello1"}, {10, "hello2"}, {3, "hello3"}};
    std::sort(hello.begin(), hello.end(), [](Hello & h1, Hello & h2) {
        return h1.a > h2.a;
    });
    for (auto & h : hello) {
        SPDLOG_INFO("{} {}", h.a, h.b);
    }
    
    // 稳定排序，相等的元素相对顺序不会发生变化，使用的是归并排序，sort使用快排或者堆排序
    std::stable_sort(hello.begin(), hello.end(), [](Hello h1, Hello h2) {
        return h1.b > h2.b;
    });

    auto high = std::max_element(v.begin(), v.end());
    auto low = std::min_element(v.begin(), v.end());
    SPDLOG_INFO("high[{}] low[{}]", *high, *low);

    // 用在已经排序的容器中
    auto result = std::upper_bound(v.begin(), v.end(), 4);
    SPDLOG_INFO("first > 4 [{}]", *result);

    result = std::lower_bound(v.begin(), v.end(), 100);

    {
        // 部分排序 [first, middle)， last
        // first,last是作为范围，first，middle表示这部分需要排序
        // 感觉表达不清楚
        std::vector<int> v{1, 100, 10, 9, 90, 2, 3, 200};
        std::partial_sort(v.begin(), v.begin()+3, v.end());
        show(v);
    }

    {
        // 查找第一个没排序的元素
        std::vector<int> v{1, 100, 10, 9, 90, 2, 3, 200};
        auto result = std::is_sorted_until(v.begin(), v.end());
        SPDLOG_INFO("not sort [{}]", *result);
    }

    {
        // 部分拷贝
        std::vector<int> v{1, 100, 10, 9, 90, 2, 3, 200};
        std::vector<int> copy(4);
        std::partial_sort_copy(v.begin(), v.end(), copy.begin(), copy.end());
        show(copy);
    }

    {
        // 对 std::unordered_map/map 使用排序直接报错
        // std::unordered_map<int, std::string> m {{1, "hello"}, {2, "world"}};
        // sort(m.begin(), m.end());
        // std::map<int, std::string> m {{1, "hello"}, {2, "world"}};
        // sort(m.begin(), m.end());
    }

    return 0;
}