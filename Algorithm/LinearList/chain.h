//
// Created by GentleCold on 2022/8/17.
// 由单向链表描述的线性表模板类
//

#ifndef MYTINYALGORITHM_CHAIN_H
#define MYTINYALGORITHM_CHAIN_H

#include "linear_list.h"
#include <cassert>

namespace myalm {


// declare

template <class T>
struct ChainNode {
    T value;
    ChainNode<T> *next = nullptr;

    ChainNode() = default;
    explicit ChainNode(const T& value) { this -> value = value; }
    ChainNode(const T& value, ChainNode<T> *next) {
        this -> value = value;
        this -> next = next;
    }
};

template <class T>
class Chain : public LinearList<T> {
public:
    Chain();
    Chain(const Chain<T>&);
    ~Chain();

    // ADT
    bool empty() const { return _size == 0; }
    int size() const { return _size; }
    T& get(int index) const;
    int index_of(const T& value) const;
    void erase(int index);
    void insert(int index, const T& value);
    void push_back(const T& value);
    void clear();

    // more
    T& operator[](int index) const { return get(index); }

    // iterator
    class iterator;
    iterator begin() { return iterator(_head -> next); }
    iterator end() { return iterator(nullptr); }

protected:
    ChainNode<T> *_head = nullptr;
    int _size = 0;
};

template <class T>
Chain<T>::Chain() {
    _head = new ChainNode<T>;
}

template <class T>
Chain<T>::Chain(const Chain<T>& v) {
    _size = v._size;
    _head = new ChainNode<T>;
    ChainNode<T> *leftNode = _head;
    ChainNode<T> *rightNode = v._head -> next;
    for (int i = 0; i < _size; i++) {
        leftNode -> next = new ChainNode<T>(rightNode -> value);
        leftNode = leftNode -> next;
        rightNode = rightNode -> next;
    }
}

template <class T>
Chain<T>::~Chain() {
    while (_head != nullptr) {
        ChainNode<T> *p = _head;
        _head = _head -> next;
        delete p;
    }
}

template <class T>
T& Chain<T>::get(int index) const {
    assert(index >= 0 && index < _size);

    ChainNode<T> *currentNode = _head -> next;
    while (index) {
        index--;
        currentNode = currentNode -> next;
    }

    return currentNode -> value;
}

template <class T>
int Chain<T>::index_of(const T& v) const {
    int index = 0;
    ChainNode<T> *currentNode = _head -> next;

    while (currentNode) {
        if (currentNode -> value == v) {
            return index;
        }
        currentNode = currentNode -> next;
        index++;
    }

    return -1;
}

template <class T>
void Chain<T>::erase(int index) {
    assert(index >= 0 && index < _size);

    ChainNode<T> *p = _head;
    while (index) {
        index--;
        p = p -> next;
    }

    ChainNode<T> *deleteNode = p -> next;
    p -> next = p -> next -> next;
    delete deleteNode;
    _size--;
}

template<class T>
void Chain<T>::insert(int index, const T& v) {
    assert(index >= 0 && index <= _size);

    ChainNode<T> *p = _head;
    while (index) {
        index--;
        p = p -> next;
    }
    p -> next = new ChainNode<T>(v, p -> next);
    _size++;
}

template<class T>
void Chain<T>::push_back(const T &v) {
    insert(_size, v);
}

template<class T>
void Chain<T>::clear() {
    ChainNode<T> *p = _head -> next;
    while (p) {
        ChainNode<T> *t = p;
        p = p -> next;
        delete t;
    }
    _size = 0;
    _head -> next = nullptr;
}

template <class T>
class Chain<T>::iterator {
public:
    // constructor
    explicit iterator(ChainNode<T> *node = nullptr) { this -> node = node; }

    // de-referencing operators
    T& operator*() const { return node -> value; }
    T* operator->() const { return &node -> value; }

    // increment
    iterator& operator++() { node = node -> next; return *this; }
    iterator operator++(int) {
        iterator old = *this;
        node = node -> next;
        return old;
    }

    // equality testing
    bool operator!=(const iterator right) const {
        return node != right.node;
    }

    bool operator==(const iterator right) const{
        return node == right.node;
    }

protected:
    ChainNode<T>* node;
};


}

#endif //MYTINYALGORITHM_CHAIN_H
