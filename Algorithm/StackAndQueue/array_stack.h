//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_ARRAY_STACK_H
#define MYTINYALGORITHM_ARRAY_STACK_H

#include <cassert>

namespace myalm {


template <class T>
class ArrayStack {
public:
    explicit ArrayStack(int initialCapacity = 10);
    ~ArrayStack() { delete [] _stack; }

    bool empty() const { return _top == 0; }
    int size() const { return _top; }

    void push(const T& value);
    void pop();
    const T& top() const;
protected:
    void _setCapacity(int newCapacity);
    T* _stack = nullptr;
    int _top = 0;
    int _capacity = 0;
};

template <class T>
ArrayStack<T>::ArrayStack(int initialCapacity) {
    assert(initialCapacity > 1);
    _capacity = initialCapacity;
    _stack = new T[_capacity];
}

template <class T>
void ArrayStack<T>::_setCapacity(int newCapacity) {
    assert(newCapacity > _top);
    T* tmp = new T[newCapacity];
    std::copy(_stack, _stack + _top, tmp);
    delete [] _stack;
    _stack = tmp;
    _capacity = newCapacity;
}

template <class T>
void ArrayStack<T>::push(const T& value) {
    if (_top == _capacity) {
        _setCapacity(_capacity * 1.5);
    }

    _stack[_top++] = value;
}

template <class T>
const T& ArrayStack<T>::top() const {
    assert(_top > 0);
    return _stack[_top - 1];
}

template <class T>
void ArrayStack<T>::pop() {
    assert(_top > 0);
    _stack[--_top].~T();

    if (_top < _capacity / 4) {
        _setCapacity(_capacity / 2);
    }
}


}


#endif //MYTINYALGORITHM_ARRAY_STACK_H
