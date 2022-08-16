//
// Created by GentleCold on 2022/8/17.
//

#ifndef MYTINYALGORITHM_TEST_H
#define MYTINYALGORITHM_TEST_H

#include <cstdio>
#include <cstring>

int main_ret = 0;
int test_count = 0;
int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)\
    do {\
        test_count++;\
        if (equality) {\
            test_pass++;\
        } else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")
#define EXPECT_EQ_DOUBLE(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%lf")
#define EXPECT_EQ_TRUE(actual) EXPECT_EQ_BASE(actual, "true", "false", "%s")

#endif //MYTINYALGORITHM_TEST_H
