#include <iostream>
#include <memory>
#ifndef _MSC_VER
#    include <cxxabi.h>
#endif

#include <gtest/gtest.h>


// reference from https://stackoverflow.com/a/20170989 by Howard Hinnant
template<class T>
std::string type_name() {
    using TR = typename std::remove_reference<T>::type;
    std::unique_ptr<char, void (*)(void *)> own(
#ifndef _MSC_VER
            abi::__cxa_demangle(typeid(TR).name(), nullptr,
                                nullptr, nullptr),
#else
            nullptr,
#endif
            std::free
    );
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

/// Bad Case
template<typename T>
void may_forward_arg(T t) {
    std::cout << type_name<T>() << " -> " << type_name<decltype(t)>() << std::endl;
}

/// Bad Case
template<typename T>
void may_forward_arg_l(T &t) {
    std::cout << type_name<T>() << " -> " << type_name<decltype(t)>() << std::endl;
}

/// Good Case
template<typename T>
void may_forward_arg_r(T &&t) {
    std::cout << type_name<T>() << " -> " << type_name<decltype(t)>() << std::endl;
    // normally, std::forward may be used here for perfectly forwarding
    // parameters down to the callees. To be concrete, std::forward will:
    //   1. forwards lvalues as either lvalues or rvalues, depending on T; or
    //   2. forwards rvalues as rvalues, which may be a returned value, instead
    //      of lvalues.
}


TEST(FORWARD, validateForwardMechanism) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    int a = 0;
    int &b = a;

    const int ca = 0;
    const int &cb = ca;

    may_forward_arg(a);
    may_forward_arg(b);
    may_forward_arg(ca);
    may_forward_arg(cb);
    may_forward_arg(0);

    std::cout << std::endl;

    may_forward_arg_l(a);
    may_forward_arg_l(b);
    may_forward_arg_l(ca);
    may_forward_arg_l(cb);
    //may_forward_arg_l(0);

    std::cout << std::endl;

    may_forward_arg_r(a);
    may_forward_arg_r(b);
    may_forward_arg_r(ca);
    may_forward_arg_r(cb);
    may_forward_arg_r(0);

    std::cout << std::endl;

    using int_l = int &;
    using int_r = int &&;

    std::cout << "int:      \t" << type_name<int>() << std::endl;
    std::cout << "int&:     \t" << type_name<int&>() << std::endl;
    std::cout << "int& &:   \t" << type_name<int_l &>() << std::endl;
    std::cout << "int& &&:  \t" << type_name<int_l &&>() << std::endl;
    std::cout << "int&&:    \t" << type_name<int&&>() << std::endl;
    std::cout << "int&& &:  \t" << type_name<int_r &>() << std::endl;
    std::cout << "int&& &&: \t" << type_name<int_r &&>() << std::endl;
}
