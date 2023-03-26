#include "3rdparty.h"

// 关系型容器

int main()
{
    spdlog_init();

    std::map<int, std::string> m;

    m.insert(std::make_pair(1, "hello"));
    m.insert(std::make_pair(2, "world"));
    m.insert(std::make_pair(3, "ni"));
    // 插入会失败
    m.insert(std::make_pair(3, "hao"));

    // 但这种方式就可以
    m[3] = "buhao";

    show(m);

    return 0;
}