#include "3rdparty.h"

// 快排
// 1. 递归
// 2. 找出一个点，点的左边都小，点的右边都大
// 3. 在对两边进行排序
void quick(std::vector<int> & arr, int left, int right)
{
    if (left >= right) return;

    int n = left;
    int l = left + 1;
    int r = right;

    while (l <= r) {
        if (arr[n] < arr[l] && arr[n] > arr[r]) {
            std::swap(arr[l], arr[r]);
        }
        if (arr[n] >= arr[l]) l++;
        if (arr[n] <= arr[r]) r--;
    }

    std::swap(arr[n], arr[r]);

    quick(arr, left, r-1);
    quick(arr, r+1, right);
}

int main()
{
    spdlog_init();

    auto show = [](std::vector<int> & v) {
        SPDLOG_INFO("show vector --------------------");
        for (auto & i : v) {
            SPDLOG_INFO("value [{}]", i);
        }
    };

    std::vector<int> v{1, 2, 10, 3, 5, 100, 20};
    show(v);

    quick(v, 0, v.size()-1);
    show(v);

    return 0;
}
