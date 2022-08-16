//
// Created by GentleCold on 2022/8/17.
//

#ifndef MYTINYALGORITHM_TEST_LINEAR_LIST_H
#define MYTINYALGORITHM_TEST_LINEAR_LIST_H

#include "test.h"
#include "../Algorithm/LinearList/array_list.h"
#include "../Algorithm/LinearList/chain.h"

static void test_array_list() {
    myalm::ArrayList<int> v(10);

    EXPECT_EQ_TRUE(v.empty());
    v.push_back(11);
    EXPECT_EQ_INT(11, v.get(0));
    v.push_back(2);
    v.push_back(3);
    EXPECT_EQ_INT(1, v.index_of(2));
    EXPECT_EQ_INT(3, v.size());
    v.erase(1);
    EXPECT_EQ_INT(2, v.size());
    v.clear();
    EXPECT_EQ_INT(0, v.size());
}

static void test_chain() {
    // myalm::Chain<int> v;
}

void test_linear_list() {
    test_array_list();
    test_chain();
}

#endif //MYTINYALGORITHM_TEST_LINEAR_LIST_H
