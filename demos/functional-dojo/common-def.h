#ifndef DOJO_DEMOS_FUNCTIONAL_DOJO_COMMON_DEF_H_
#define DOJO_DEMOS_FUNCTIONAL_DOJO_COMMON_DEF_H_

struct Foo {
    int data = 10;

    int print_sum(int a, int b) const {
        return a + b + data;
    }
};

#endif //DOJO_DEMOS_FUNCTIONAL_DOJO_COMMON_DEF_H_
