//
// Created by GentleCold on 2022/9/2.
//

#ifndef MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H
#define MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H

#include "test.h"
#include "../Algorithm/StackAndQueue/array_stack.h"
#include "../Algorithm/StackAndQueue/array_queue.h"
#include "../Algorithm/StackAndQueue/priority_queue.h"
#include "../Algorithm/StackAndQueue/fib_priority_queue.h"
#include "../Algorithm/StackAndQueue/Application/heap_sort.h"

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

static void test_priority_queue() {
    myalm::PriorityQueue<int> v;

    for (int i = 0; i < 15; i++) {
        v.push(i);
    }
    EXPECT_EQ_INT(14, v.top());
    for (int i = 0; i < 5; i++) {
        v.pop();
    }
    EXPECT_EQ_INT(9, v.top());
    for (int i = 0; i < 9; i++) {
        v.pop();
    }
    EXPECT_EQ_INT(0, v.top());
}

static void test_fib_priority_queue() {
    myalm::FibPriorityQueue<int> v;

    for (int i = 0; i < 150; i++) {
        v.push(i);
    }
    EXPECT_EQ_INT(149, v.top());
    for (int i = 0; i < 50; i++) {
        v.pop();
    }
    EXPECT_EQ_INT(99, v.top());
    for (int i = 0; i < 99; i++) {
        v.pop();
    }
    EXPECT_EQ_INT(0, v.top());

    myalm::FibPriorityQueue<int> v2;
    for (int i = 0; i < 15; i++) {
        v2.push(i);
    }
    v.merge(v2);
    EXPECT_EQ_INT(14, v.top());
    v.push(20);
    v.push(20);
    v.pop();
    EXPECT_EQ_INT(20, v.top());
}

// Application

static void test_heap_sort() {
    int *v = new int[100];

    for (int i = 0; i < 100; i++) {
        v[i] = rand();
    }

    myalm::heap_sort(v, 100);

    bool flag = true;
    for (int i = 0; i < 99; i++) {
        if (v[i] > v[i + 1]) {
            flag = false;
            break;
        }
    }

    EXPECT_EQ_TRUE(flag);
    delete [] v;
}

void test_stack_and_queue() {
    test_array_queue();
    test_array_stack();
    test_priority_queue();
    test_fib_priority_queue();

    test_heap_sort();
}

#endif //MYTINYALGORITHM_TEST_STACK_AND_QUEUE_H
