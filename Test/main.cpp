//
// Created by GentleCold on 2022/8/17.
//

#include "test_linear_list.h"

void test_all() {
    test_linear_list();
}

int main() {
    test_all();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}