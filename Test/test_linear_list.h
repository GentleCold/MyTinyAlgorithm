//
// Created by GentleCold on 2022/8/17.
//

#ifndef MYTINYALGORITHM_TEST_LINEAR_LIST_H
#define MYTINYALGORITHM_TEST_LINEAR_LIST_H

#include <numeric>
#include "test.h"
#include "../Algorithm/LinearList/array_list.h"
#include "../Algorithm/LinearList/chain.h"
#include "../Algorithm/LinearList/Application/bin_sort.h"
#include "../Algorithm/LinearList/Application/radix_sort.h"

// class test

static void test_array_list() {
    myalm::ArrayList<int> v(2);

    EXPECT_EQ_TRUE(v.empty());
    v.push_back(11);
    v.push_back(2);
    v.push_back(3);
    myalm::ArrayList<int> v1(v);
    EXPECT_EQ_INT(16, std::accumulate(v1.begin(), v1.end(), 0));
    EXPECT_EQ_INT(11, v1[0]);
    EXPECT_EQ_INT(3, v1[2]);
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

    v1.insert(0, 1);
    EXPECT_EQ_INT(1, v1[0]);
    v1.insert(0, 2);
    EXPECT_EQ_INT(2, v1[0]);

//    // test for pressure
//    for (int i = 0; i < 100000; i++) {
//        v1.push_back(i);
//        EXPECT_EQ_INT(i, v1.get(i));
//    }
//
//    v1.clear();
//    EXPECT_EQ_INT(2, v1.capacity());
}

static void test_chain() {
    myalm::Chain<int> v;

    EXPECT_EQ_TRUE(v.empty());
    v.push_back(11);
    v.push_back(2);
    v.push_back(3);
    myalm::Chain<int> v1(v);
    EXPECT_EQ_INT(16, std::accumulate(v1.begin(), v1.end(), 0));
    EXPECT_EQ_INT(11, v1[0]);
    EXPECT_EQ_INT(3, v1[2]);
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

    v1.insert(0, 1);
    EXPECT_EQ_INT(1, v1[0]);
    v1.insert(0, 2);
    EXPECT_EQ_INT(2, v1[0]);
}

// application test

static void test_bin_sort() {
    myalm::Chain<int> v;

    for (int i = 0; i < 10; i++) {
        int element = rand() % 10 + 1; // range [1, 10]
        v.push_back(element);
    }

    myalm::bin_sort(v, 10);

    bool flag = true;
    for (int i = 0; i < 9; i++) {
        if (v[i] > v[i + 1]) {
            flag = false;
            break;
        }
    }

    EXPECT_EQ_TRUE(flag);
};

static void test_radix_sort() {
    myalm::Chain<int> v;

    for (int i = 0; i < 10; i++) {
        int element = rand() % 999 + 1; // range [1, 999]
        v.push_back(element);
    }

    myalm::radix_sort(v, 3);

    bool flag = true;
    for (int i = 0; i < 9; i++) {
        if (v[i] > v[i + 1]) {
            flag = false;
            break;
        }
    }

    EXPECT_EQ_TRUE(flag);
}

void test_linear_list() {
    test_array_list();
    test_chain();

    test_bin_sort();
    test_radix_sort();
}

#endif //MYTINYALGORITHM_TEST_LINEAR_LIST_H
