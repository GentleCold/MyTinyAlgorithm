//
// Created by GentleCold on 2022/8/30.
//

#ifndef MYTINYALGORITHM_MERGE_SORT_H
#define MYTINYALGORITHM_MERGE_SORT_H

#include "../array_list.h"

namespace myalm {

template <class T>
void _merge(ArrayList<T>& v, int b, int m, int e) {
    ArrayList<T> tmp;
    for (int i = b; i < e; i++) {
        tmp.push_back(v[i]);
    }
    int i = 0, j = m - b, k = b;

    while (i < m - b && j < e - b) {
        v[k++] = (tmp[i] < tmp[j]) ? tmp[i++] : tmp[j++];
    }

    while (i < m - b) {
        v[k++] = tmp[i++];
    }

    while (j < e - b) {
        v[k++] = tmp[j++];
    }
}

template <class T>
void _merge_sort(ArrayList<T>& v, int b, int e) { // [b, e)
    int m;
    if (b < e - 1) {
        m = (b + e) / 2;
        _merge_sort(v, b, m);
        _merge_sort(v, m, e);
        _merge(v, b, m, e);
    }
}

template <class T>
void merge_sort(ArrayList<T>& v) {
    _merge_sort(v, 0, v.size());
}


}


#endif //MYTINYALGORITHM_MERGE_SORT_H
