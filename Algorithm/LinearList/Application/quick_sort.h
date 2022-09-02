//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_QUICK_SORT_H
#define MYTINYALGORITHM_QUICK_SORT_H


namespace myalm {


template <class T>
static inline void _swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <class T>
static int _partition(ArrayList<T>& v, int b, int e) {
    int k = rand() % (e - b) + b, i = b, j = b;
    _swap(v[k], v[e - 1]);

    for (; j < e - 1; j++) {
        if (v[j] < v[e - 1]) {
            _swap(v[j], v[i]);
            i++;
        }
    }

    _swap(v[i], v[e - 1]);
    return i;
}

template <class T>
static void _quick_sort(ArrayList<T>& v, int b, int e) {
    if (b < e - 1) {
        int q = _partition(v, b, e);
        _quick_sort(v, b, q);
        _quick_sort(v, q + 1, e);
    }
}

template <class T>
void quick_sort(ArrayList<T>& v) {
    _quick_sort(v, 0, v.size());
}


}


#endif //MYTINYALGORITHM_QUICK_SORT_H
