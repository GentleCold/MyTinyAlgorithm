//
// Created by GentleCold 2022/9/3.
//

#ifndef MYTINYALGORITHM_HEAP_SORT_H
#define MYTINYALGORITHM_HEAP_SORT_H

#include "../priority_queue.h"

namespace myalm {


template <class T>
void heap_sort(T *a, int size) {
    PriorityQueue<T> heap;
    heap.initialize(a, size);

    while (size) {
        size--;
        a[size] = heap.top();
    }
}


}

#endif //MYTINYALGORITHM_HEAP_SORT_H
