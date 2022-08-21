//
// Created by GentleCold on 2022/8/18.
// 为 Chain 适配的箱子排序
//

#include "../chain.h"

namespace myalm {


// max 代表最大值

template <class T>
void bin_sort(Chain<T>& v, int max) {
    Chain<T> *bin;
    bin = new Chain<T>[max + 1];

    int num = v.size();
    for (int i = 0; i < num; i++) {
        T element = v[0];
        v.erase(0);
        bin[(unsigned int)element].insert(0, element);
    }

    for (int i = max; i >= 0; i--) {
        while (!bin[i].empty()) {
            T element = bin[i][0];
            bin[i].erase(0);
            v.insert(0, element);
        }
    }

    delete [] bin;
}


}

