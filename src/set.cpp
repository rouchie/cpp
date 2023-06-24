#include "3rdparty.h"

// set:
//     平衡二叉树
//     有序，必须支持比较运算
//     支持正反向迭代器
// unordered_set:
//     哈希表
//     无序，必须支持哈希运算
//     支持正向迭代器，不支持反向迭代器

class A {
    public:
        int a = 10;
};

int main()
{
    spdlog_init();

    {
        std::set<A> a;
        a.emplace(A());
        a.emplace(A());
        a.emplace(A());
        a.emplace(A());

        for (auto it = a.begin(); it != a.end(); it++) {
            // it->a = 1024;
            // 返回的迭代器都是const类型的，所以没法直接赋值
        }

        std::set<A*> b;
        b.emplace(new A);
        b.emplace(new A);
        b.emplace(new A);
        b.emplace(new A);

        for (auto it = a.begin(); it != a.end(); it++) {
            // (*it).a = 10;
        }
    }

    std::set<int> s0 {1, 2, 3, 4, 10};
    std::set<int, std::greater<int>> s1 {1, 2, 3, 4, 10};
    std::set<int, std::greater<int>> s2 {std::begin(s1), std::end(s1)};

    int v[] = {10, 100};

    s0.insert(8);
    s0.insert(80);
    s0.insert(800);
    s0.insert({9, 90});
    s0.insert(std::begin(v), std::end(v));

    for (auto & s : s0) {
        SPDLOG_INFO("s0 v[{}]", s);
    }

    s0.erase(8);
    s0.erase(8);
    auto it = s0.erase(s0.begin());
    s0.erase(it);

    for (auto & s : s0) {
        SPDLOG_INFO("s0 v[{}]", s);
    }

    for (auto & s : s1) {
        SPDLOG_INFO("s1 v[{}]", s);
    }

    for (auto & s : s2) {
        SPDLOG_INFO("s2 v[{}]", s);
    }


    return 0;
}