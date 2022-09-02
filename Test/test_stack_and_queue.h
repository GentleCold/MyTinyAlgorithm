//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H
#define MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H

#include "test.h"
#include "../Algorithm/StackAndQueue/array_stack.h"
#include "../Algorithm/StackAndQueue/array_queue.h"

static void test_array_queue() {
    myalm::ArrayQueue<int> v;
    EXPECT_EQ_TRUE(v.empty());
    v.push(1);
    v.push(2);
    v.push(3);
    EXPECT_EQ_INT(3, v.size());
    EXPECT_EQ_INT(3, v.back());
    EXPECT_EQ_INT(1, v.front());
    v.pop();
    EXPECT_EQ_INT(2, v.size());
    EXPECT_EQ_INT(3, v.back());
    EXPECT_EQ_INT(2, v.front());
    v.pop();
    v.pop();
    EXPECT_EQ_INT(0, v.size());

    for (int i = 0; i < 9; i++) {
        v.push(i);
    }

    EXPECT_EQ_INT(0, v.front());
    EXPECT_EQ_INT(8, v.back());
    EXPECT_EQ_INT(9, v.size());

    for (int i = 9; i < 109; i++) {
        v.push(i);
    }

    EXPECT_EQ_INT(0, v.front());
    EXPECT_EQ_INT(108, v.back());
    EXPECT_EQ_INT(109, v.size());

    for (int i = 0; i < 100; i++) {
        v.pop();
    }

    EXPECT_EQ_INT(100, v.front());
    EXPECT_EQ_INT(108, v.back());
    EXPECT_EQ_INT(9, v.size());
}

static void test_array_stack() {
    myalm::ArrayStack<int> v;
    EXPECT_EQ_TRUE(v.empty());
    v.push(1);
    v.push(2);
    v.push(3);
    EXPECT_EQ_INT(3, v.size());
    EXPECT_EQ_INT(3, v.top());
    v.pop();
    EXPECT_EQ_INT(2, v.size());
    EXPECT_EQ_INT(2, v.top());
}

void test_stack_and_queue() {
    test_array_queue();
    test_array_stack();
}

#endif //MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H
