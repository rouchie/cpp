#include "3rdparty.h"

// O(nlogn)

int main()
{
    spdlog_init();

    std::vector<int> v{1, 100, 2, 3, 200, 4, 100};

    show(v, "before heap sort");

    show(v, "after heap sort");

    return 0;
}