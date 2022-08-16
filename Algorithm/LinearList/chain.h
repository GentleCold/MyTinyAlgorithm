//
// Created by GentleCold on 2022/8/17.
// 由链表描述的线性表模板类
//

#ifndef MYTINYALGORITHM_CHAIN_H
#define MYTINYALGORITHM_CHAIN_H

#include "linear_list.h"

namespace myalm {


// declare

template<class T>
class Chain : public LinearList<T> {
public:
    Chain(int initialCapacity = 10);
    Chain(const Chain<T>&);
    ~Chain() { delete [] _array; }

    // ADT
    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    T& get(int index) const;
    int indexOf(const T& element) const;
    void erase(int index);
    void insert(int index, const T& element);
    virtual void push_back(const T& element);
    virtual void clear();

    // more
    int capacity() const { return capacity; }

    // iterator
    class iterator;
    iterator begin() { return iterator(_array); }
    iterator end() { return iterator(_array + _capacity); }

protected:
    T* _array = nullptr;
    int _size = 0;
    int _capacity = 0;
};



}

#endif //MYTINYALGORITHM_CHAIN_H
