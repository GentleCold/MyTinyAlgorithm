//
// Created by GentleCold on 2022/8/18.
// 为 Chain 适配的基数排序
//

#include "../chain.h"

namespace myalm {


template <class T>
static void _bin_sort(Chain<T>& v, int bit) {
    Chain<T> *bin;
    bin = new Chain<T>[10];

    // 得到 10 ^ bit
    int radix = 1;
    while (bit) {
        bit--;
        radix *= 10;
    }

    int num = v.size();
    for (int i = 0; i < num; i++) {
        T element = v[0];
        v.erase(0);
        bin[((unsigned int)element % radix) / (radix / 10)].insert(0, element);
    }

    for (int i = 9; i >= 0; i--) {
        while (!bin[i].empty()) {
            T element = bin[i][0];
            bin[i].erase(0);
            v.insert(0, element);
        }
    }

    delete [] bin;
}

// maxBit 最大位数
template <class T>
void radix_sort(myalm::Chain<T>& v, int maxBit) {
    // 以 bin_sort 进行 maxBit 次排序
    for (int i = 1; i <= maxBit; i++) {
        _bin_sort(v, i);
    }
}


}


