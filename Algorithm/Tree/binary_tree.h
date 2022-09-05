//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_BINARY_TREE_H
#define MYTINYALGORITHM_BINARY_TREE_H

#include "../StackAndQueue/array_queue.h"

namespace myalm {


template <class T>
struct BinaryTreeNode {
    bool color = true; // true = red
    T value;
    BinaryTreeNode<T> *left = nullptr, *right = nullptr, *p;

    explicit BinaryTreeNode(const T& value): value(value) { p = this; }

    BinaryTreeNode(const T& value, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right) {
        this -> value = value;
        this -> left = left;
        this -> right = right;
    }
};

template <class T>
class BinaryTree {
public:
    ~BinaryTree() { clear(); }
    bool empty() const { return _size == 0; }
    int size() const { return _size; }

    void pre_order(void (*visit)(BinaryTreeNode<T> *)) {
        assert(visit != nullptr);
        _visit = visit;
        _pre_order(_root);
    }

    void in_order(void (*visit)(BinaryTreeNode<T> *)) {
        assert(visit != nullptr);
        _visit = visit;
        _in_order(_root);
    }

    void post_order(void (*visit)(BinaryTreeNode<T> *)) {
        assert(visit != nullptr);
        _visit = visit;
        _post_order(_root);
    }

    void level_order(void (*visit)(BinaryTreeNode<T> *)) {
        assert(visit != nullptr);
        _visit = visit;
        _level_order(_root);
    }

    void clear() {
        post_order(_dispose);
        _root = nullptr;
        _size = 0;
    }

protected:
    BinaryTreeNode<T> *_root = nullptr;
    int _size = 0;

private:
    static void (*_visit)(BinaryTreeNode<T> *t);
    static void _pre_order(BinaryTreeNode<T> *t);
    static void _in_order(BinaryTreeNode<T> *t);
    static void _post_order(BinaryTreeNode<T> *t);
    static void _level_order(BinaryTreeNode<T> *t);

    static void _dispose(BinaryTreeNode<T> *t) { delete t; }
};

// declare or error
template <class T>
void (*BinaryTree<T>::_visit)(BinaryTreeNode<T> *t);

template <class T>
void BinaryTree<T>::_pre_order(BinaryTreeNode<T> *t) {
    if (t) {
        _visit(t);
        _pre_order(t -> left);
        _pre_order(t -> right);
    }
}

template <class T>
void BinaryTree<T>::_in_order(BinaryTreeNode<T> *t) {
    if (t) {
        _in_order(t -> left);
        _visit(t);
        _in_order(t -> right);
    }
}

template <class T>
void BinaryTree<T>::_post_order(BinaryTreeNode<T> *t) {
    if (t) {
        _post_order(t -> left);
        _post_order(t -> right);
        _visit(t);
    }
}

template <class T>
void BinaryTree<T>::_level_order(BinaryTreeNode<T> *t) {
    ArrayQueue<BinaryTreeNode<T>*> q;

    if (t) q.push(t);
    while (!q.empty()) {
        t = q.front();
        q.pop();

        _visit(t);

        if (t -> left) q.push(t -> left);
        if (t -> right) q.push(t -> right);
    }
}


}
#endif //MYTINYALGORITHM_BINARY_TREE_H
