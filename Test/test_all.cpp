//
// Created by GentleCold on 2022/8/17.
//

#include "test_linear_list.h"
#include "test_tree.h"
#include "test_stack_and_queue.h"
#include "test_map_and_set.h"
#include "test_graph.h"

//#pragma GCC optimize(2)

void test_all() {
    test_linear_list();
    test_tree();
    test_stack_and_queue();
    test_map_and_set();
    test_graph();
}

int main() {
    test_all();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}