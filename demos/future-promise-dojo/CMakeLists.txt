add_executable(future_promise_dojo dojo.cpp)
target_link_libraries(future_promise_dojo
    GTest::gtest GTest::gtest_main)

set_target_properties(future_promise_dojo
    PROPERTIES
    CXX_STANDARD 11)
