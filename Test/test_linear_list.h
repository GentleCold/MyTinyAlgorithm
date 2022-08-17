//
// Created by GentleCold on 2022/8/17.
//

#ifndef MYTINYALGORITHM_TEST_LINEAR_LIST_H
#define MYTINYALGORITHM_TEST_LINEAR_LIST_H

#include <numeric>
#include "test.h"
#include "../Algorithm/LinearList/array_list.h"
#include "../Algorithm/LinearList/chain.h"

static void test_array_list() {
    myalm::ArrayList<int> v(2);

    EXPECT_EQ_TRUE(v.empty());
    v.push_back(11);
    v.push_back(2);
    v.push_back(3);
    myalm::ArrayList<int> v1(v);
    EXPECT_EQ_INT(16, std::accumulate(v1.begin(), v1.end(), 0));
    EXPECT_EQ_INT(11, v1.get(0));
    EXPECT_EQ_INT(3, v1.get(2));
    EXPECT_EQ_INT(1, v1.index_of(2));
    EXPECT_EQ_INT(-1, v1.index_of(100));
    EXPECT_EQ_INT(3, v1.size());
    EXPECT_EQ_INT(3, v1.capacity());
    v1.erase(1);
    EXPECT_EQ_INT(2, v1.size());
    v1.insert(0, 1);
    EXPECT_EQ_INT(1, v1.get(0));
    v1.clear();
    EXPECT_EQ_INT(0, v1.size());
    v1.push_back(1);
    v1.erase(0);
    EXPECT_EQ_INT(2, v1.capacity());
}

static void test_chain() {
    myalm::Chain<int> v;

    EXPECT_EQ_TRUE(v.empty());
    v.push_back(11);
    v.push_back(2);
    v.push_back(3);
    myalm::Chain<int> v1(v);
    EXPECT_EQ_INT(16, std::accumulate(v1.begin(), v1.end(), 0));
    EXPECT_EQ_INT(11, v1.get(0));
    EXPECT_EQ_INT(3, v1.get(2));
    EXPECT_EQ_INT(1, v1.index_of(2));
    EXPECT_EQ_INT(-1, v1.index_of(100));
    EXPECT_EQ_INT(3, v1.size());
    v1.erase(1);
    EXPECT_EQ_INT(2, v1.size());
    v1.insert(0, 1);
    EXPECT_EQ_INT(1, v1.get(0));
    v1.clear();
    EXPECT_EQ_INT(0, v1.size());
    v1.push_back(1);
    v1.erase(0);
}

void test_linear_list() {
    test_array_list();
    test_chain();
}

#endif //MYTINYALGORITHM_TEST_LINEAR_LIST_H
