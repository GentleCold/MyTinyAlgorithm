//
// Created by GentleCold on 2022/9/3.
//

#ifndef MYTINYALGORITHM_TEST_MAP_AND_SET_H
#define MYTINYALGORITHM_TEST_MAP_AND_SET_H

#include "test.h"
#include "../Algorithm/MapAndSet/hash_map.h"

static void test_hash_map() {
    myalm::HashMap<char, int> v;
    EXPECT_EQ_TRUE(!v.find('a'));
    v.insert(std::pair<char, int>('a', 10));
    v.insert(std::pair<char, int>('e', 11));
    v.insert(std::pair<char, int>('g', 12));
    v.insert(std::pair<char, int>('z', 13));

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

    myalm::HashMap<std::string, int> v2;
    v2.insert(std::pair<std::string, int>("ab", 0));
    v2.insert(std::pair<std::string, int>("ac", 1));
    v2.insert(std::pair<std::string, int>("aa", 2));
    v2.erase("ab");
    v2.erase("ab");
    v2.erase("aa");
    v2.erase("ac");
    v2.erase("error");
    EXPECT_EQ_TRUE(v2.empty());
}

void test_map_and_set() {
    test_hash_map();
}

#endif //MYTINYALGORITHM_TEST_MAP_AND_SET_H
