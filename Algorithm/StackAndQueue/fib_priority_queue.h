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
    // bool mark = false;

    FibHeapNode<T> // *p = nullptr,
                   *child = nullptr,
                   *left = nullptr,
                   *right = nullptr;

    explicit FibHeapNode(const T& v) { value = v; left = this; right = this; }
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
    void _link_insert(FibHeapNode<T> *a, FibHeapNode<T> *b);
    void _link_erase(FibHeapNode<T> *v);
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
void FibPriorityQueue<T>::_link_insert(FibHeapNode<T> *a, FibHeapNode<T> *b) {
    // insert after a
    b -> right = a -> right;
    b -> left = a;
    a -> right -> left = b;
    a -> right = b;
}

template <class T>
void FibPriorityQueue<T>::_link_erase(FibHeapNode<T> *v) {
    v -> left -> right = v -> right;
    v -> right -> left = v -> left;
}

template <class T>
void FibPriorityQueue<T>::push(const T& v) {
    auto *x = new FibHeapNode<T>(v);
    if (_heap) {
        // insert
        _link_insert(_heap, x);

        if (v > _max -> value) {
            _max = x;
        }
    } else {
        // initialize
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
        // move child to root list
        if (z -> child) {
            FibHeapNode<T> *c = z -> child, *current;
            c -> left -> right = nullptr; // break loop
            while (c) {
                current = c -> right;
                _link_insert(z, c);
                c = current;
            }
        }

        // delete z
        if (_heap == z) _heap = z -> right;
        _link_erase(z);

        _size--;
        _max = nullptr;

        // merge root list and reset max
        if (_size) {
            _consolidate();
        } else {
            _heap = nullptr;
        }

        delete z;
    }
}

template <class T>
const T& FibPriorityQueue<T>::top() const {
    assert(_size > 0);
    return _max -> value;
}

template <class T>
void FibPriorityQueue<T>::merge(FibPriorityQueue<T>& v) {
    _heap -> left -> right = v._heap;

    FibHeapNode<T> *tmp = v._heap -> left;
    v._heap -> left = _heap -> left;
    _heap -> left = tmp;

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

    auto *degrees = new FibHeapNode<T> *[b];
    for (int i = 0; i < b; i++) degrees[i] = nullptr;
    FibHeapNode<T> *current = _heap;

    do {
        int c = current -> degree;
        while (degrees[c]) {
            FibHeapNode<T> *y = degrees[c];

            if (current == y) break; // important! get rid of duplicate

            // insure current is the max
            if (y -> value > current -> value) {
                FibHeapNode<T> *tmp = current;
                current = y;
                y = tmp;
            }

            // make y out of root list
            if (_heap == y) _heap = _heap -> right;
            _link_erase(y);

            // link y to current
            if (current -> child) {
                _link_insert(current -> child, y);
            } else {
                current -> child = y;
                // pay attention to node initialize!
                y -> right = y;
                y -> left = y;
            }

            degrees[c] = nullptr;
            (current -> degree)++;
            c++;
        }

        degrees[c] = current;
        current = current -> right;
    } while (current != _heap);

    delete [] degrees;

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
