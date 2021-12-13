add_executable(functional_dojo
    dojo-bind.cpp
    dojo-mem_fn.cpp
    )
target_link_libraries(functional_dojo
    GTest::gtest GTest::gtest_main)

set_target_properties(functional_dojo
    PROPERTIES
    CXX_STANDARD 11)
