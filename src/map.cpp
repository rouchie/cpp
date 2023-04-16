#include "3rdparty.h"

// 关系型容器

int main()
{
    spdlog_init();

    std::map<int, std::string> m;
    std::unordered_map<int, std::string> um;

    for (auto i=0; i<100; i++) {
        um[i] = fmt::format("string {}", i);
    }

    for (auto & it : um) {
        // 听说go里的map固定元素每次遍历都会有不一样的结果，测试下c++里的unordered_map，至少在100个情况下是一样的
        SPDLOG_INFO("{} - {}", it.first, it.second);
    }

    m.insert(std::make_pair(1, "hello"));
    m.insert(std::make_pair(2, "world"));
    m.insert(std::make_pair(3, "ni"));
    m.emplace(std::make_pair(4, "pink"));
    // 插入会失败，值已经存在无法更新，只能使用数组方式更新
    m.insert(std::make_pair(3, "hao"));

    show(m);

    // 但这种方式就可以
    m[3] = "buhao";

    show(m);

    return 0;
}