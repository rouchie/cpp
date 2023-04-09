#include "3rdparty.h"

template<typename T>
void s(T & v)
{
    for (auto & ii : v) {
        SPDLOG_INFO("[{}]", ii);
    }
}

int main()
{
    spdlog_init();

    std::vector<uint32_t> v;

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    v.push_back(1);

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    v.reserve(20);

    SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());

    {
        // 表示20个元素，值都是0
        std::vector<uint32_t> v(20);
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        // 表示20个元素，值都是1024
        std::vector<uint32_t> v(20, 1024);
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        // 表示1个元素, 值是20
        std::vector<uint32_t> v{20};
        SPDLOG_INFO("size[{}] capacity[{}]", v.size(), v.capacity());
    }

    {
        std::vector<uint32_t> v(20, 1024);
        for (auto ii = v.begin(); ii < v.end(); ++ii) {
            SPDLOG_INFO("[{}]", *ii);
        }

        //对于容器来说自身带的begin/end函数跟std::begin/std::end函数没有区别
        //std::begin/std::end是c++11里添加的，可以使用在数组上
        for (auto ii = std::begin(v); ii < std::end(v); ++ii) {
            SPDLOG_INFO("[{}]", *ii);
        }

        const char name[] = "rouchie";        
        for (auto c = std::begin(name); c < std::end(name); ++c) {
            SPDLOG_INFO("[{}]", *c);
        }
    }

    {
        // 尾部插入，emplace_back效率比push_back高
        std::vector<int> v;
        v.push_back(1);
        v.emplace_back(2);

        v.insert(v.begin(), 3);
        v.emplace(v.end(), 4);

        v.insert(v.begin(), {5, 6, 7});

        s(v);
    }

    {
        std::vector<int> v{1, 2, 2, 3, 4, 5, 2, 2, 4};

        SPDLOG_INFO("capacity [{}]", v.capacity());
        v.pop_back();

        // 去除多余的空间
        v.shrink_to_fit();
        SPDLOG_INFO("capacity [{}]", v.capacity());

        v.erase(v.begin());

        s(v);
    }

    {
        SPDLOG_INFO("---");

        std::vector<int> v{1, 2, 2, 3, 4, 5, 2, 2, 4};

        // remove 本身并不删除元素，还会占有位置，可以配合erase删除
        auto it = std::remove(std::begin(v), std::end(v), 2);
        s(v);

        SPDLOG_INFO("---");

        v.erase(it, std::end(v));
        s(v);
    }

    return 0;
}