#include <gtest/gtest.h>

#include "common-def.h"

TEST(FUNCTIONAL_MEM_FN, memFunc) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    Foo foo;
    auto fn = std::mem_fn(&Foo::print_sum);
    ASSERT_EQ(fn(&foo, 10, 20), foo.print_sum(10, 20));
}

TEST(FUNCTIONAL_MEM_FN, memData) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    Foo foo;
    auto fn = std::mem_fn(&Foo::data);
    foo.data = 20;
    ASSERT_EQ(fn(&foo), foo.data);
}
