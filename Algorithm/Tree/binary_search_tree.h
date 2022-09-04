//
// Created by GentleCold on 2022/9/4.
//

#ifndef MYTINYALGORITHM_BINARY_SEARCH_TREE_H
#define MYTINYALGORITHM_BINARY_SEARCH_TREE_H

#include "binary_tree.h"

namespace myalm {


template <class K, class V>
class BinarySearchTree : public BinaryTree<std::pair<const K, V> > {
public:
    std::pair<const K, V>* find(const K&) const;
    std::pair<const K, V>* max() const;
    std::pair<const K, V>* min() const;
    std::pair<const K, V>* prev(const K&) const;
    std::pair<const K, V>* next(const K&) const;
    void insert(const std::pair<const K, V>&);
    void erase(const K&);

protected:
    BinaryTreeNode<std::pair<const K, V>>* _search(const K&) const;
    BinaryTreeNode<std::pair<const K, V>>* _prev(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _next(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _max(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _min(BinaryTreeNode<std::pair<const K, V>> *) const;
};

template <class K, class V>
void BinarySearchTree<K, V>::insert(const std::pair<const K, V> &v) {
    BinaryTreeNode<std::pair<const K, V>> *p = BinaryTree<std::pair<const K, V>>::_root,
                                          *pp = nullptr;
    while (p) {
        pp = p;
        if (p -> value.first > v.first) {
            p = p -> left;
        } else if (p -> value.first < v.first) {
            p = p -> right;
        } else {
            p -> value.second = v.second;
            return;
        }
    }

    auto *node = new BinaryTreeNode<std::pair<const K, V>>(v);
    if (!BinaryTree<std::pair<const K, V>>::_root) {
        BinaryTree<std::pair<const K, V>>::_root = node;
    } else {
        if (pp -> value.first > v.first) {
            pp -> left = node;
        } else {
            pp -> right = node;
        }
        node -> p = pp;
    }

    BinaryTree<std::pair<const K, V>>::_size++;
}

template <class K, class V>
void BinarySearchTree<K, V>::erase(const K& key) {
    BinaryTreeNode<std::pair<const K, V>> *p = BinaryTree<std::pair<const K, V>>::_root,
                                          *pp = nullptr;
    while (p) {
        if (p -> value.first > key) {
            p = p -> left;
        } else if (p -> value.first < key) {
            p = p -> right;
        } else {
            break;
        }
        pp = p;
    }

    if (p) {
        BinaryTreeNode<std::pair<const K, V>> *c = (p -> right) ? p -> right : p -> left;

        // have both right and left
        if (p -> right && p -> left) {
            c = _next(p);
            if (c == p -> right) {
                c -> left = p -> left;
                p -> left -> p = c;
            } else {
                c -> p -> left = c -> right;
                c -> right -> p = c -> p;

                c -> left = p -> left;
                c -> right = p -> right;
                p -> left -> p = c;
                p -> right -> p = c;
            }
        }

        // set parent node
        if (pp) {
            if (key > pp -> value.first) {
                pp -> right = c;
            } else {
                pp -> left = c;
            }
            c -> p = pp;
        } else {
            BinaryTree<std::pair<const K, V>>::_root = c;
            c -> p = c;
        }

        delete p;
    }
}

template <class K, class V>
std::pair<const K, V>* BinarySearchTree<K, V>::find(const K& key) const {
    return (_search(key)) ? &_search(key) -> value : nullptr;
}

template <class K, class V>
std::pair<const K, V>* BinarySearchTree<K, V>::prev(const K& key) const {
    auto *p = _search(key);
    return (_prev(p)) ? &_prev(p) -> value : nullptr;
}

template <class K, class V>
std::pair<const K, V>* BinarySearchTree<K, V>::next(const K& key) const {
    auto *p = _search(key);
    return (_next(p)) ? &_next(p) -> value : nullptr;
}

template <class K, class V>
std::pair<const K, V>* BinarySearchTree<K, V>::max() const {
    return (_max(BinaryTree<std::pair<const K, V>>::_root)) ? &_max(BinaryTree<std::pair<const K, V>>::_root) -> value : nullptr;
}

template <class K, class V>
std::pair<const K, V>* BinarySearchTree<K, V>::min() const {
    return (_max(BinaryTree<std::pair<const K, V>>::_root)) ? &_min(BinaryTree<std::pair<const K, V>>::_root) -> value : nullptr;
}

template <class K, class V>
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_search(const K& key) const {
    BinaryTreeNode<std::pair<const K, V>> *p = BinaryTree<std::pair<const K, V>>::_root;
    while (p) {
        if (p -> value.first > key) {
            p = p -> left;
        } else if (p -> value.first < key) {
            p = p -> right;
        } else {
            return p;
        }
    }
    return nullptr;
}

template <class K, class V>
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_max(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (p) {
        while (p -> right) {
            p = p -> right;
        }
        return p;
    }
    return nullptr;
}

template <class K, class V>
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_min(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (p) {
        while (p -> left) {
            p = p -> left;
        }
        return p;
    }
    return nullptr;
}

template <class K, class V>
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_prev(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (p) {
        if (p -> left) {
            return _max(p -> left);
        } else {
            while (p -> p != p) {
                if (p -> p -> right == p) return p -> p;
                p = p -> p;
            }
        }
    }
    return nullptr;
}

template <class K, class V>
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_next(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (p) {
        if (p -> right) {
            return _min(p -> right);
        } else {
            while (p -> p != p) {
                if (p -> p -> left == p) return p -> p;
                p = p -> p;
            }
        }
    }
    return nullptr;
}



}

#endif //MYTINYALGORITHM_BINARY_SEARCH_TREE_H
