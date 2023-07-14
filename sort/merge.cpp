#include "3rdparty.h"

// O(nlogn)
// 其实就是分成最小单位，排序后再合并
// 稳定排序，相对位置不会改变
// 需要额外空间

void merge(std::vector<int>& v, int left, int mid, int right)
{
    std::vector<int> tmp(right - left + 1);
    int l = left;
    int r = mid+1;
    int n = 0;

    while (l <= mid && r <= right) {
        if (v[l] <= v[r]) {
            tmp[n++] = v[l++];
        } else {
            tmp[n++] = v[r++];
        }
    }

    while (l <= mid) {
        tmp[n++] = v[l++];
    }

    while (r <= right) {
        tmp[n++] = v[r++];
    }

    for (unsigned i=0; i<tmp.size(); i++) {
        v[left+i] = tmp[i];
    }
}

void mergeSort(std::vector<int>& v, int left, int right)
{
    if (left >= right) return ;

    int mid = (right + left) / 2;

    mergeSort(v, left, mid);
    mergeSort(v, mid+1, right);

    merge(v, left, mid, right);
}

int main()
{
    spdlog_init();

    std::vector<int> v{1, 100, 2, 3, 200, 4, 100};

    show(v, "before merge sort");

    mergeSort(v, 0, v.size() - 1);

    show(v, "after merge sort");

    return 0;
}
