#include "3rdparty.h"

int main()
{
    spdlog_init();

    std::vector<int> v0 {0, 1, 2, 3 ,4, 8, 9, 6};
    std::vector<int> v1(v0.size()*2);

    // 基本用法
    copy(std::begin(v0), std::end(v0), std::begin(v1));
    show(v1);

    SPDLOG_INFO("v0.size[{}] v1.size[{}]", v0.size(), v1.size());
    
    // 更简单的拷贝，有缺陷，两个会完全一样，copy不会覆盖多出来的空间
    std::vector<int> v2(v0.size()*2);
    v2 = v0;
    SPDLOG_INFO("v0.size[{}] v2.size[{}]", v0.size(), v2.size());

    show(v2);

    std::vector<int> v3(v0.size());
    // 部分拷贝
    copy(std::begin(v0), std::begin(v0)+2, std::begin(v3));
    show(v3);

    copy_n(std::begin(v0), 3, std::begin(v3));
    show(v3);

    // std::back_inserter 从后方插入
    std::vector<int> v4(v0.size());
    std::copy_if(std::begin(v0), std::end(v0), std::back_inserter(v4), [](int v) { return v % 2 == 0; });
    show(v4);

    // std::back_inserter/std::front_inserter，这两个是会插入元素的，不像std::begin，他们只是使用当前的迭代器
    // copy_backward 从后往前拷
    std::vector<int> v5(v0.size() * 2);
    std::copy_backward(std::begin(v0), std::end(v0), std::end(v5));
    show(v5, "copy_backward");

    // v5会变长
    std::copy(std::begin(v0), std::end(v0), std::back_inserter(v5));
    show(v5, "copy + back_inserter");

    // v6并没有预先分配空间，front_inserter会插入相应的元素
    std::vector<int> v6;
    std::copy(std::begin(v0), std::end(v0), std::back_inserter(v6));
    // std::copy(std::begin(v0), std::end(v0), std::front_inserter<std::vector<int>>(v6));
    show(v6, "copy + font_inserter");

    return 0;
}