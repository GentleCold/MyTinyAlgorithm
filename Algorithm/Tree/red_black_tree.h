//
// Created by GentleCold on 2022/9/4.
//

#ifndef MYTINYALGORITHM_RED_BLACK_TREE_H
#define MYTINYALGORITHM_RED_BLACK_TREE_H

#include "binary_search_tree.h"

namespace myalm {


template <class K, class V>
class RedBlackTree : public BinarySearchTree<K, V> {
public:
    void insert(const std::pair<const K, V>&) override;
    void erase(const K&) override;

#ifdef DEBUG
    int test_if_red_black_tree();
    bool _test_if_red_link_red(BinaryTreeNode<std::pair<const K, V>> *p) const;
    int _test_if_black_height_equal(BinaryTreeNode<std::pair<const K, V>> *p) const;
#endif
protected:
    void _left_rotate(BinaryTreeNode<std::pair<const K, V>> *x);
    void _right_rotate(BinaryTreeNode<std::pair<const K, V>> *x);
};

template <class K, class V>
void RedBlackTree<K, V>::insert(const std::pair<const K, V> &v) {
    BinaryTreeNode<std::pair<const K, V>> *p = BinarySearchTree<K, V>::_insert(v); // insert new node
    if (!p) return; // if the node is exiting

    // justify node
    while (p -> p -> color) {
        // if p is not root
        if (p -> p != p) {
            // if pp is in left
            if (p -> p == p -> p -> p -> left) {
                BinaryTreeNode<std::pair<const K, V>> *y = p -> p -> p -> right;
                if (y && y -> color) { // case 1
                    p -> p -> color = false;
                    y -> color = false;
                    y -> p -> color = true;
                    p = p -> p -> p;
                    continue;
                } else if (p == p -> p -> right) { // case 2
                    p = p -> p;
                    _left_rotate(p);
                }
                // case 3
                p -> p -> color = false;
                p -> p -> p -> color = true;
                _right_rotate(p -> p -> p);
            } else {  // if pp is in right, same as left
                BinaryTreeNode<std::pair<const K, V>> *y = p -> p -> p -> left;
                if (y && y -> color) { // case 1
                    p -> p -> color = false;
                    y -> color = false;
                    y -> p -> color = true;
                    p = p -> p -> p;
                    continue;
                } else if (p == p -> p -> left) { // case 2
                    p = p -> p;
                    _right_rotate(p);
                }
                // case 3
                p -> p -> color = false;
                p -> p -> p -> color = true;
                _left_rotate(p -> p -> p);
            }
        }
        BinaryTree<std::pair<const K, V>>::_root -> color = false;
    }
}

template <class K, class V>
void RedBlackTree<K, V>::erase(const K& key) {
    BinaryTreeNode<std::pair<const K, V>> *p = BinarySearchTree<K, V>::_search(key);
    if (!p) return;

    BinaryTreeNode<std::pair<const K, V>> *c = (p -> right) ? p -> right : p -> left, *x = c, *xp = p -> p;
    bool color = p -> color;

    // have both right and left
    if (p -> right && p -> left) {
        c = BinarySearchTree<K, V>::_next(p);
        // c must have
        // c is not child of p, make p = c, delete c, c -> right is another c, save in x
        color = c -> color;
        c -> color = p -> color;
        x = c -> right;

        if (c == p -> right) {
            xp = c; // in this case, c -> p == p is deleted and xp is still c

            c -> left = p -> left;
            p -> left -> p = c;
        } else {
            x = c -> right;
            xp = c -> p;

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

    delete p;
    if (!(--BinaryTree<std::pair<const K, V>>::_size)) return;

    // justify color, in this case, p have zero or one child
    if (!color && xp) {
        // x is not root and x -> color is black or x is nullptr
        while (!x || (!x -> color && x -> p != x)) {
            // in this case, x must have an uncle
            if (xp -> left == x) {
                BinaryTreeNode<std::pair<const K, V>> *u = xp -> right;
                if (u -> color) { // case 1
                    u -> color = false;
                    xp -> color = true;
                    _left_rotate(xp);
                    u = xp -> right;
                }

                if (!x || (!u -> left -> color && !u -> right -> color)) { // case 2
                    u -> color = true;
                    x = xp;
                    xp = x -> p;
                    continue;
                }

                if (u -> left -> color && !u -> right -> color) { // case 3
                    u -> color = true;
                    u -> left -> color = false;
                    _right_rotate(u);
                    u = xp -> right;
                }

                // case 4
                u -> color = xp -> color;
                xp -> color = false;
                _left_rotate(xp);
                x = BinaryTree<std::pair<const K, V>>::_root;
            } else { // the same
                BinaryTreeNode<std::pair<const K, V>> *u = xp -> left;
                if (u -> color) { // case 1
                    u -> color = false;
                    xp -> color = true;
                    _right_rotate(xp);
                    u = xp -> left;
                }

                if (!x || (!u -> left -> color && !u -> right -> color)) { // case 2
                    u -> color = true;
                    x = xp;
                    xp = x -> p;
                    continue;
                }

                if (u -> right -> color && !u -> left -> color) { // case 3
                    u -> color = true;
                    u -> right -> color = false;
                    _left_rotate(u);
                    u = xp -> left;
                }

                // case 4
                u -> color = xp -> color;
                xp -> color = false;
                _right_rotate(xp);
                x = BinaryTree<std::pair<const K, V>>::_root;
            }
        }

        x -> color = false;
    }
}

template <class K, class V>
void RedBlackTree<K, V>::_left_rotate(BinaryTreeNode <std::pair<const K, V>> *x) {
    BinaryTreeNode <std::pair<const K, V>> *y = x -> right;
    assert(y != nullptr);
    // link left of y to right of x
    x -> right = y -> left;
    if (y -> left) y -> left -> p = x;

    // if x is root
    if (x -> p == x) {
        BinaryTree<std::pair<const K, V>>::_root = y;
        y -> p = y;
    } else {
        y -> p = x -> p;
        if (x -> p -> left == x) x -> p -> left = y;
        else x -> p -> right = y;
    }

    // link x to left of y
    y -> left = x;
    x -> p = y;
}

template <class K, class V>
void RedBlackTree<K, V>::_right_rotate(BinaryTreeNode <std::pair<const K, V>> *x) {
    BinaryTreeNode <std::pair<const K, V>> *y = x -> left;
    assert(y != nullptr);
    x -> left = y -> right;
    if (y -> right) y -> right -> p = x;
    if (x -> p == x) {
        BinaryTree<std::pair<const K, V>>::_root = y;
        y -> p = y;
    } else {
        y -> p = x -> p;
        if (x -> p -> right == x) x -> p -> right = y;
        else x -> p -> left = y;
    }

    y -> right = x;
    x -> p = y;
}

// test function
#ifdef DEBUG
template <class K, class V>
int RedBlackTree<K, V>::test_if_red_black_tree() {
    BinaryTreeNode<std::pair<const K, V>> *p = BinaryTree<std::pair<const K, V>>::_root;
    if (!p) return 0;
    if (p -> color) return 1; // root color error
    if (_test_if_black_height_equal(p) == -1) return 2; // black height error
    if (!_test_if_red_link_red(p)) return 3; // red link red error
    if (!BinarySearchTree<K, V>::test_if_binary_search_tree()) return 4; // binary search tree error
    return 0;
}

template <class K, class V>
bool RedBlackTree<K, V>::_test_if_red_link_red(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (!p) return true;
    bool flag = _test_if_red_link_red(p -> left) && _test_if_red_link_red(p -> right);
    if (!flag) return false;
    if (p -> color && (((p -> left) && p -> left -> color) || ((p -> left) && p -> left -> color)))
        return false;
    return true;
}

template <class K, class V>
int RedBlackTree<K, V>::_test_if_black_height_equal(BinaryTreeNode<std::pair<const K, V>> *p) const {
    if (!p) return 1;
    int i = _test_if_black_height_equal(p -> left);
    int j = _test_if_black_height_equal(p -> right);
    if (i != j || i == -1 || j == -1) return -1;
    if (!p -> color) {
        return i + 1;
    }
    return i;
}
#endif


}


#endif //MYTINYALGORITHM_RED_BLACK_TREE_H
