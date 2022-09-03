//
// Created by GentleCold on 2022/9/3.
//

#ifndef MYTINYALGORITHM_FIB_PRIORITY_QUEUE_H
#define MYTINYALGORITHM_FIB_PRIORITY_QUEUE_H

#include <cassert>

namespace myalm {


template <class T>
struct FibHeapNode {
    T value;
    int degree = 0;
    bool mark = false;

    FibHeapNode<T> *p = nullptr,
                   *child = nullptr,
                   *left = nullptr,
                   *right = nullptr;

    explicit FibHeapNode(const T& v) { value = v; left = this; right = this; }
    FibHeapNode(const T& v, FibHeapNode<T> *l, FibHeapNode<T> *r) {
        value = v;
        left = l;
        right = r;
    }
};

template <class T>
class FibPriorityQueue {
public:
    ~FibPriorityQueue();

    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    void push(const T& v);
    void pop();
    const T& top() const;
    void merge(FibPriorityQueue<T>&);

private:
    void _consolidate();
    void _dispose(FibHeapNode<T> *v);
    FibHeapNode<T> *_heap = nullptr;
    FibHeapNode<T> *_max = nullptr;
    int _size = 0;
};

template <class T>
FibPriorityQueue<T>::~FibPriorityQueue() {
    _dispose(_heap);
}

template <class T>
void FibPriorityQueue<T>::_dispose(FibHeapNode<T> *v) {
    if (v) {
        v -> left -> right = nullptr;
        FibHeapNode<T> *current = v;
        while (v) {
            current = current -> right;
            _dispose(v -> child);
            delete v;
            v = current;
        }
    }
}

template <class T>
void FibPriorityQueue<T>::push(const T& v) {
    if (_heap) {
        auto *x = new FibHeapNode<T>(v, _heap, _heap -> right);
        // insert
        x -> left -> right = x;
        x -> right -> left = x;

        if (v > _max -> value) {
            _max = x;
        }
    } else {
        // initialize
        auto *x = new FibHeapNode<T>(v);
        _heap = x;
        _max = x;
    }

    _size++;
}

template <class T>
void FibPriorityQueue<T>::pop() {
    assert(_size > 0);
    FibHeapNode<T> *z = _max;
    if (z) {
        // delete z and move child to root list
        while ((z -> degree) > 0) {
            // z = z;
            FibHeapNode<T> *tmp = z -> child -> right;
            z -> child -> p = nullptr;
            z -> child -> left -> right = z -> child -> right;
            z -> child -> right -> left = z -> child -> left;

            z -> child -> right = z -> right;
            z -> child -> left = z;
            z -> right -> left = z -> child;
            z -> right  = z -> child;

            (z -> degree)--;
            z -> child = (z -> degree) ? tmp : nullptr;
        }

        if (_heap == z) _heap = z -> right;
        z -> left -> right = z -> right;
        z -> right -> left = z -> left;

        _size--;

        // consolidate the root list
        if (z == z -> right) {
            _heap = _max = nullptr;
        } else {
            _max = nullptr;
            _consolidate();
        }
    }
    delete z;
}

template <class T>
const T& FibPriorityQueue<T>::top() const {
    assert(_size > 0);
    return _max -> value;
}

template <class T>
void FibPriorityQueue<T>::merge(FibPriorityQueue<T>& v) {
    _heap -> left -> right = v._heap;
    v._heap -> left = _heap -> left;
    _heap -> left = v._heap -> left;
    _heap -> left -> right = _heap;

    if (!_max || (v._max && v._max -> value > _max -> value))
        _max = v._max;

    _size += v._size;

    // clear v
    v._heap = v._max = nullptr;
    v._size = 0;
}

template <class T>
void FibPriorityQueue<T>::_consolidate() {
    // lg(size)
    int a = _size, b = 0;
    while (a) {
        a /= 2;
        b++;
    }

    FibHeapNode<T> *degrees[b] = { 0 };
    FibHeapNode<T> *current = _heap;
    do {
        int c = current -> degree;
        while (degrees[c]) {
            FibHeapNode<T> *y = degrees[c];

            if (current == y) break; // important!

            if (y -> value > current -> value) {
                FibHeapNode<T> *tmp = current;
                current = y;
                y = tmp;
            }

            // make y out of root list
            if (_heap == y) _heap = _heap -> right;
            y -> right -> left = y -> left;
            y -> left -> right = y -> right;

            // link y to current
            if (current -> child) {
                y -> p = current;
                y -> right = current -> child -> right;
                y -> left = current -> child;
                current -> child -> right -> left = y;
                current -> child -> right = y;
            } else {
                current -> child = y;
                // pay attention to node initialize!
                y -> right = y;
                y -> left = y;
                y -> p = current;
            }

            degrees[c] = nullptr;
            (current -> degree)++;
            c++;
        }

        degrees[c] = current;
        current = current -> right;
    } while (current != _heap);

    // get max
    current = _heap -> right;
    _max = _heap;
    while (current != _heap) { // loop condition!
        if (_max -> value < current -> value) {
            _max = current;
        }

        current = current -> right;
    }
}


}

#endif //MYTINYALGORITHM_FIB_PRIORITY_QUEUE_H
