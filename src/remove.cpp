#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v{1, 2, 3, 4, 3, 5, 6};

    SPDLOG_INFO("before remove size [{}]", v.size());
    show(v, "before remove");

    // remove 并不会改变容器大小，后面的成员会往前挪，返回的是新的结束点
    auto e = std::remove(v.begin(), v.end(), 3);

    SPDLOG_INFO("after remove size [{}]", v.size());
    show(v, "after remove");

    v.erase(e, v.end());
    show(v, "after erase");

    e = std::remove_if(v.begin(), v.end(), [](const int& i) { return i==2; });
    show(v, "after remove_if");

    v.erase(e, v.end());
    show(v, "after erase");

    return 0;
}