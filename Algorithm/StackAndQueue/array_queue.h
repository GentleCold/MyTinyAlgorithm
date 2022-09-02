//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_ARRAY_QUEUE_H
#define MYTINYALGORITHM_ARRAY_QUEUE_H

#include <cassert>

namespace myalm {


template <class T>
class ArrayQueue {
public:
    explicit ArrayQueue(int initialCapacity = 10);
    ~ArrayQueue() { delete [] _queue; }

    bool empty() const { return _front == _back; }
    int size() const { return (_back - _front + _capacity) % _capacity; }

    void push(const T& value);
    void pop();
    T& front() const;
    T& back() const;
protected:
    void _setCapacity(int newCapacity);
    T* _queue = nullptr;
    int _front = 0;
    int _back = 0;
    int _capacity = 0;
};

template <class T>
ArrayQueue<T>::ArrayQueue(int initialCapacity) {
    assert(initialCapacity > 1);
    _capacity = initialCapacity;
    _queue = new T[_capacity];
}

template <class T>
void ArrayQueue<T>::_setCapacity(int newCapacity) {
    int size = this -> size();
    assert(newCapacity > size);
    T* tmp = new T[newCapacity];

    if (_front <= _back) {
        std::copy(_queue + _front, _queue + _back, tmp);
    } else {
        std::copy(_queue + _front, _queue + _capacity, tmp);
        std::copy(_queue, _queue + _back, tmp + _capacity - _front);
    }

    _front = 0;
    _back = size;
    delete [] _queue;
    _queue = tmp;
    _capacity = newCapacity;
}

template <class T>
void ArrayQueue<T>::push(const T& value) {
    if ((_back + 1) % _capacity == _front) {
        _setCapacity(_capacity * 1.5);
    }

    _queue[_back] = value;
    _back = (_back + 1) % _capacity;
}

template <class T>
void ArrayQueue<T>::pop() {
    assert(_back != _front);

    _queue[_front].~T();
    _front = (_front + 1) % _capacity;

    if (size() < _capacity / 4) {
        _setCapacity(_capacity / 2);
    }
}

template <class T>
T& ArrayQueue<T>::front() const {
    assert(_back != _front);
    return _queue[_front];
}

template <class T>
T& ArrayQueue<T>::back() const {
    assert(_back != _front);
    return _queue[(_back - 1 + _capacity) % _capacity];
}


}

#endif //MYTINYALGORITHM_ARRAY_QUEUE_H
