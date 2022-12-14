//
// Created by GentleCold on 2022/8/17.
// 由数组描述的线性表模板类
//

#ifndef MYTINYALGORITHM_ARRAY_LIST_H
#define MYTINYALGORITHM_ARRAY_LIST_H

#include "linear_list.h"
#include <cassert>
#include <algorithm>

namespace myalm {


// declare

template<class T>
class ArrayList : public LinearList<T> {
public:
    explicit ArrayList(int initialCapacity = 10);
    ArrayList(const ArrayList<T>&);
    ~ArrayList() { delete [] _array; }

    // ADT
    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    T& get(int index) const;
    int index_of(const T& value) const;
    void erase(int index);
    void insert(int index, const T& value);
    void clear();

    // more
    int capacity() const { return _capacity; }
    void push_back(const T& value);
    void pop_back();
    T& operator[](int index) const { return get(index); }
    void swap(int a, int b);

    // iterator
    class iterator;
    iterator begin() { return iterator(_array); }
    iterator end() { return iterator(_array + _capacity); }

protected:
    void _setCapacity(int newCapacity);
    T* _array = nullptr;
    int _size = 0;
    int _capacity = 0;
};

// define

template <class T>
ArrayList<T>::ArrayList(int initialCapacity) {
    assert(initialCapacity > 1);
    _capacity = initialCapacity;
    _array = new T[_capacity];
}

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& v) {
    _size = v._size;
    _capacity = v._capacity;
    _array = new T[_capacity];
    std::copy(v._array, v._array + _size, _array);
}

template <class T>
T& ArrayList<T>::get(int index) const {
    assert(index >= 0 && index < _size);
    return _array[index];
}

template <class T>
int ArrayList<T>::index_of(const T& value) const {
    int index = (int)(std::find(_array, _array + _size, value) - _array);
    return (index == _size) ? -1 : index;
}

template <class T>
void ArrayList<T>::erase(int index) {
    assert(index >= 0 && index < _size);
    std::copy(_array + index + 1, _array + _size, _array + index);
    _array[--_size].~T();

    if (_size < _capacity / 4) {
        _setCapacity(_capacity / 2);
    }
}

template <class T>
void ArrayList<T>::insert(int index, const T& value) {
    assert(index >= 0 && index <= _size);

    if (_size == _capacity) {
        _setCapacity(_capacity * 1.5);
    }

    std::copy_backward(_array + index, _array + _size, _array + _size + 1);
    _array[index] = value;
    _size++;
}

template <class T>
void ArrayList<T>::push_back(const T& value) {
    if (_size == _capacity) {
        _setCapacity(_capacity * 1.5);
    }

    _array[_size++] = value;
}

template <class T>
void ArrayList<T>::pop_back() {
    _array[--_size].~T();

    if (_size < _capacity / 4) {
        _setCapacity(_capacity / 2);
    }
}

template <class T>
void ArrayList<T>::clear() {
    while (_size) {
        _array[--_size].~T();
    }

    _setCapacity(2);
}

template <class T>
void ArrayList<T>::swap(int a, int b) {
    assert(a >= 0 && a < _size && b >= 0 && b < _size);
    T tmp = get(a);
    get(a) = get(b);
    get(b) = tmp;
}

template <class T>
void ArrayList<T>::_setCapacity(int newCapacity) {
    assert(newCapacity > _size);
    T* temp = new T[newCapacity];
    std::copy(_array, _array + _size, temp);
    delete [] _array;
    _array = temp;
    _capacity = newCapacity;
}

template <class T>
class ArrayList<T>::iterator {
public:
    // 代表双向迭代器

    explicit iterator(T* thePosition = 0) { position = thePosition; }

    T& operator*() const { return *position; }
    T* operator->() const { return &*position; }

    iterator& operator++() { ++position; return *this; }
    iterator operator++(int) {
        iterator old = *this;
        ++position;
        return old;
    }

    iterator& operator--() { --position; return *this; }
    iterator operator--(int) {
        iterator old = *this;
        --position;
        return old;
    }

    bool operator!=(const iterator right) const {
        return position != right.position;
    }

    bool operator==(const iterator right) const {
        return position == right.position;
    }

protected:
    T* position;
};



}

#endif //MYTINYALGORITHM_ARRAY_LIST_H
