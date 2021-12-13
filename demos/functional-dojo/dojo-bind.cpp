#include <gtest/gtest.h>

#include "common-def.h"

int foo(int const a, std::string const& b, double c) {
    return a + static_cast<int>(b.size()) - static_cast<int>(c);
}

int bar(int a) {
    return a + 2;
}

TEST(FUNCTIONAL_BIND, completeBind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto bound_foo = std::bind(foo, 10, "hello", 1.2);
    ASSERT_EQ(bound_foo(), foo(10, "hello", 1.2));
}

TEST(FUNCTIONAL_BIND, partialBind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;  // for _1, _2, ...
    auto partial_bound_foo = std::bind(foo, 10, _2, _1);
    ASSERT_EQ(partial_bound_foo(1.2, "hello"), foo(10, "hello", 1.2));
}

TEST(FUNCTIONAL_BIND, autoEvalNestBind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;
    auto bound_foo = std::bind(foo, std::bind(bar, 10), "hello", 1.2);
    ASSERT_EQ(bound_foo(), foo(bar(10), "hello", 1.2));
}

TEST(FUNCTIONAL_BIND, sharedPlaceholder) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;
    auto bound_foo = std::bind(foo, std::bind(bar, _1), "hello", _1);
    ASSERT_EQ(bound_foo(10), foo(bar(10), "hello", 10));
}

TEST(FUNCTIONAL_BIND, memberFuncBind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;
    Foo foo;
    auto bound_foo = std::bind(&Foo::print_sum, &foo, 10, _1);
    ASSERT_EQ(bound_foo(10), foo.print_sum(10, 10));
}

TEST(FUNCTIONAL_BIND, memberDataBind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;
    Foo foo;
    auto bound_foo = std::bind(&Foo::data, _1);
    foo.data = 12;
    ASSERT_EQ(bound_foo(foo), foo.data);
}
