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
    virtual void insert(const std::pair<const K, V>&);
    virtual void erase(const K&);

#ifdef DEBUG
    bool test_if_binary_search_tree();
    bool _test_if_binary_search_tree(BinaryTreeNode<std::pair<const K, V>>*);
#endif

protected:
    BinaryTreeNode<std::pair<const K, V>>* _insert(const std::pair<const K, V> &);
    BinaryTreeNode<std::pair<const K, V>>* _search(const K&) const;
    BinaryTreeNode<std::pair<const K, V>>* _prev(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _next(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _max(BinaryTreeNode<std::pair<const K, V>> *) const;
    BinaryTreeNode<std::pair<const K, V>>* _min(BinaryTreeNode<std::pair<const K, V>> *) const;
};

template <class K, class V>
void BinarySearchTree<K, V>::insert(const std::pair<const K, V>& v) {
    _insert(v);
}

template <class K, class V>
void BinarySearchTree<K, V>::erase(const K& key) {
    BinaryTreeNode<std::pair<const K, V>> *p = _search(key);

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
                if (c -> right) c -> right -> p = c -> p; // pay attention to nullptr case

                c -> left = p -> left;
                c -> right = p -> right;
                p -> left -> p = c;
                p -> right -> p = c;
            }
        }

        // set parent node
        if (p -> p != p) {
            if (key > p -> p -> value.first) {
                p -> p -> right = c;
            } else {
                p -> p -> left = c;
            }
            if (c) c -> p = p -> p;
        } else {
            // if delete root
            BinaryTree<std::pair<const K, V>>::_root = c;
            if (c) c -> p = c;
        }

        BinaryTree<std::pair<const K, V>>::_size--;
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
BinaryTreeNode<std::pair<const K, V>>* BinarySearchTree<K, V>::_insert(const std::pair<const K, V> &v) {
    // return address of new node, if exiting, return nullptr
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
            return nullptr;
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
    return node;
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

// test function

#ifdef DEBUG
template <class K, class V>
bool BinarySearchTree<K, V>::test_if_binary_search_tree() {
    BinaryTreeNode<std::pair<const K, V>> *p = BinaryTree<std::pair<const K, V>>::_root;
    BinaryTree<std::pair<const K, V>>::_root = nullptr;
    bool flag = _test_if_binary_search_tree(p);
    BinaryTree<std::pair<const K, V>>::_root = p;
    return flag;
}

template <class K, class V>
bool BinarySearchTree<K, V>::_test_if_binary_search_tree(BinaryTreeNode<std::pair<const K, V>>* p) {
    if (!p) return true;
    if (!_test_if_binary_search_tree(p -> left)) return false;

    if (!BinaryTree<std::pair<const K, V>>::_root) {
        BinaryTree<std::pair<const K, V>>::_root = p;
        return true;
    } else if (p -> value.first < BinaryTree<std::pair<const K, V>>::_root -> value.first) return false;

    BinaryTree<std::pair<const K, V>>::_root = p;
    if (!_test_if_binary_search_tree(p -> right)) return false;
    return true;
}
#endif

}

#endif //MYTINYALGORITHM_BINARY_SEARCH_TREE_H
