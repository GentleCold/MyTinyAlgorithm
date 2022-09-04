//
// Created by GentleCold on 2022/9/3.
//

#ifndef MYTINYALGORITHM_TEST_MAP_AND_SET_H
#define MYTINYALGORITHM_TEST_MAP_AND_SET_H

#include "test.h"
#include "../Algorithm/MapAndSet/hash_map.h"

static void test_hash_map() {
    myalm::HashMap<char, int> v(10);
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
    v.erase('h');
    EXPECT_EQ_INT(0, v.find('a'));
    EXPECT_EQ_INT(9, v.find('z') -> second);
    EXPECT_EQ_INT(12, v.find('g') -> second);
    EXPECT_EQ_INT(0, v.find('b'));
}

void test_map_and_set() {
    test_hash_map();
}

#endif //MYTINYALGORITHM_TEST_MAP_AND_SET_H
