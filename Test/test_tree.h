//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_TEST_TREE_H
#define MYTINYALGORITHM_TEST_TREE_H

#include <string>
#include "test.h"
#include "../Algorithm/Tree/binary_search_tree.h"
#include "../Algorithm/Tree/red_black_tree.h"

static void test_binary_search_tree() {
    myalm::BinarySearchTree<char, int> v;
    EXPECT_EQ_TRUE(!v.find('a'));
    EXPECT_EQ_TRUE(!v.max());
    EXPECT_EQ_TRUE(!v.min());
    EXPECT_EQ_TRUE(!v.prev('a'));
    v.insert(std::pair<char, int>('a', 10));
    v.insert(std::pair<char, int>('e', 11));
    v.insert(std::pair<char, int>('g', 12));
    v.insert(std::pair<char, int>('z', 13));

#ifdef DEBUG
    EXPECT_EQ_TRUE(v.test_if_binary_search_tree());
#endif

    EXPECT_EQ_INT(10, v.find('a') -> second);
    EXPECT_EQ_INT(12, v.find('g') -> second);
    EXPECT_EQ_TRUE(!v.find('b'));

    v.insert(std::pair<char, int>('z', 9));

    EXPECT_EQ_INT(9, v.find('z') -> second);
    v.erase('a');
    EXPECT_EQ_TRUE(!v.find('a'));
    EXPECT_EQ_INT(9, v.find('z') -> second);
    EXPECT_EQ_INT(12, v.find('g') -> second);
    EXPECT_EQ_TRUE(!v.find('b'));

    EXPECT_EQ_INT(9, v.max() -> second);
    EXPECT_EQ_INT(11, v.min() -> second);
    EXPECT_EQ_INT(11, v.prev('g') -> second);
    EXPECT_EQ_INT(9, v.next('g') -> second);
    EXPECT_EQ_TRUE(!v.prev('e'));

    myalm::BinarySearchTree<std::string, int> v2;
    v2.insert(std::pair<std::string, int>("ab", 0));
    v2.insert(std::pair<std::string, int>("ac", 1));
    v2.insert(std::pair<std::string, int>("aa", 2));
    v2.erase("ab");
    EXPECT_EQ_INT(1, v2.max() -> second);
    v2.erase("ab");
    v2.erase("aa");
    v2.erase("ac");
    v2.erase("error");
    EXPECT_EQ_TRUE(v2.empty());
}

static void test_red_black_tree() {
    myalm::RedBlackTree<char, int> v;
    v.insert(std::pair<char, int>('a', 0));
    v.insert(std::pair<char, int>('b', 1));
    v.insert(std::pair<char, int>('c', 2));
    v.insert(std::pair<char, int>('d', 3));
    v.insert(std::pair<char, int>('e', 0));
    v.insert(std::pair<char, int>('f', 1));
    v.insert(std::pair<char, int>('g', 2));
    v.insert(std::pair<char, int>('z', 3));
    v.insert(std::pair<char, int>('h', 4));
    v.insert(std::pair<char, int>('a', 1));
    v.insert(std::pair<char, int>('i', 0));
    v.insert(std::pair<char, int>('l', 1));
    v.insert(std::pair<char, int>('o', 2));
    v.insert(std::pair<char, int>('t', 3));
    v.insert(std::pair<char, int>('s', 4));
    v.insert(std::pair<char, int>('y', 1));
#ifdef DEBUG
    EXPECT_EQ_INT(0, v.test_if_red_black_tree());
#endif
    EXPECT_EQ_INT(1, v.find('a') -> second);
    v.erase('a');
    v.erase('h');
    v.erase('z');
    v.erase('c');
    v.erase('d');
    v.erase('g');
    v.erase('e');
#ifdef DEBUG
    EXPECT_EQ_INT(0, v.test_if_red_black_tree());
#endif
    v.erase('b');
    v.erase('f');
    v.erase('y');
    v.erase('t');
    v.erase('s');
    v.erase('l');
    v.erase('i');
#ifdef DEBUG
    EXPECT_EQ_INT(0, v.test_if_red_black_tree());
#endif
}

void test_tree() {
    test_binary_search_tree();
    test_red_black_tree();
}

#endif //MYTINYALGORITHM_TEST_TREE_H
