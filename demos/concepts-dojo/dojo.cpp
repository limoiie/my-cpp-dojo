#include <iostream>

#include <gtest/gtest.h>


/// define concepts - way 1
template<typename T>
concept is_int = std::is_integral_v<T>;

/// define concepts - way 2
template<typename T>
concept is_callable = requires (T t) {
    t();
};


/// use concept in template function - way 1
template<typename T>
void foo(T t) requires is_callable<T> {
    t();
}

/// use concept in template function - way 2
template<typename T>
requires is_callable<T> void goo(T t) {
    t();
}

/// use concept in template function - way 3
template <is_callable T>
void hoo(T t) {
    t();
}


TEST(CONCEPTS, callConcepts) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // use concepts by calling as functions
    std::cout << is_int<unsigned> << std::endl;
    std::cout << is_int<double> << std::endl;
}

TEST(CONCEPTS, useConceptConstrainedObject) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto const c = []() {
        std::cout << "call lambda!" << std::endl;
    };

    // use concepts constrained function
    foo(c);
    goo(c);
    hoo(c);
}
