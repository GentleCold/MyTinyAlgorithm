//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_TEST_TREE_H
#define MYTINYALGORITHM_TEST_TREE_H

#include <string>
#include "test.h"
#include "../Algorithm/Tree/binary_search_tree.h"

static void test_binary_search_tree() {
    myalm::BinarySearchTree<char, int> v;
    EXPECT_EQ_INT(0, v.find('a'));
    EXPECT_EQ_INT(0, v.max());
    EXPECT_EQ_INT(0, v.min());
    EXPECT_EQ_INT(0, v.prev('a'));
    v.insert(std::pair<char, int>('a', 10));
    v.insert(std::pair<char, int>('e', 11));
    v.insert(std::pair<char, int>('g', 12));
    v.insert(std::pair<char, int>('z', 13));

    EXPECT_EQ_INT(10, v.find('a') -> second);
    EXPECT_EQ_INT(12, v.find('g') -> second);
    EXPECT_EQ_INT(0, v.find('b'));

    v.insert(std::pair<char, int>('z', 9));

    EXPECT_EQ_INT(9, v.find('z') -> second);
    v.erase('a');
    EXPECT_EQ_INT(0, v.find('a'));
    EXPECT_EQ_INT(9, v.find('z') -> second);
    EXPECT_EQ_INT(12, v.find('g') -> second);
    EXPECT_EQ_INT(0, v.find('b'));

    EXPECT_EQ_INT(9, v.max() -> second);
    EXPECT_EQ_INT(11, v.min() -> second);
    EXPECT_EQ_INT(11, v.prev('g') -> second);
    EXPECT_EQ_INT(9, v.next('g') -> second);
    EXPECT_EQ_INT(0, v.prev('e'));

    myalm::BinarySearchTree<std::string, int> v2;
    v2.insert(std::pair<std::string, int>("ab", 0));
    v2.insert(std::pair<std::string, int>("ac", 1));
    v2.insert(std::pair<std::string, int>("aa", 2));
    v2.erase("ab");
    EXPECT_EQ_INT(1, v2.max() -> second);
}

void test_tree() {
    test_binary_search_tree();
}

#endif //MYTINYALGORITHM_TEST_TREE_H
