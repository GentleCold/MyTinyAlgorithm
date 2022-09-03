//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_PRIORITY_QUEUE_H
#define MYTINYALGORITHM_PRIORITY_QUEUE_H

#include <cassert>
#include <algorithm>

namespace myalm {


template <class T>
class PriorityQueue {
public:
    explicit PriorityQueue(int initialCapacity = 10);
    ~PriorityQueue() { delete [] _heap; }

    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    void push(const T& value);
    void pop();
    const T& top() const;
    void initialize(T*, int);
protected:
    void _setCapacity(int newCapacity);
    int _justify(int index);
    T* _heap = nullptr;
    int _size = 0;
    int _capacity = 0;
};

template <class T>
PriorityQueue<T>::PriorityQueue(int initialCapacity) {
    assert(initialCapacity > 1);
    _capacity = initialCapacity;
    _heap = new T[_capacity];
}

template <class T>
void PriorityQueue<T>::_setCapacity(int newCapacity) {
    assert(newCapacity > _size);
    T* tmp = new T[newCapacity];
    std::copy(_heap, _heap + _size + 1, tmp); // pay attention to the _size
    delete [] _heap;
    _heap = tmp;
    _capacity = newCapacity;
}

template <class T>
int PriorityQueue<T>::_justify(int index) { // pay attention to the compare with _size!
    if (index * 2 + 1 <= _size && _heap[index] < _heap[index * 2 + 1] && _heap[index * 2] < _heap[index * 2 + 1]) {
        T tmp = _heap[index];
        _heap[index] = _heap[index * 2 + 1];
        _heap[index * 2 + 1] = tmp;
        return index * 2 + 1;
    } else if (index * 2 <= _size && _heap[index] < _heap[index * 2]) {
        T tmp = _heap[index];
        _heap[index] = _heap[index * 2];
        _heap[index * 2] = tmp;
        return index * 2;
    }
    return 0;
}

template <class T>
void PriorityQueue<T>::push(const T& value) {
    if (_size + 1 == _capacity) {
        _setCapacity(_capacity * 1.5);
    }

    int k = ++_size;
    while (k > 1 && _heap[k / 2] < value) {
        _heap[k] = _heap[k / 2];
        k = k / 2;
    }

    _heap[k] = value;
}

template <class T>
const T& PriorityQueue<T>::top() const {
    assert(_size > 0);
    return _heap[1];
}

template <class T>
void PriorityQueue<T>::pop() {
    assert(_size > 0);
    _heap[1] = _heap[_size];
    _heap[_size--].~T();

    int k = 1;
    do {
        k = _justify(k);
    } while (k > 0);

    if (_size + 1 < _capacity / 4) {
        _setCapacity(_capacity / 2);
    }
}

template <class T>
void PriorityQueue<T>::initialize(T *heap, int size) {
    delete [] _heap;
    _heap = new T[10];
    _size = 0;
    _capacity = 10;

    while (size) {
        size--;
        push(heap[size]);
    }
}


}

#endif //MYTINYALGORITHM_PRIORITY_QUEUE_H
