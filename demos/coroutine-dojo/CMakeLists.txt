add_executable(coroutine_dojo dojo.cpp)
target_link_libraries(coroutine_dojo
    GTest::gtest GTest::gtest_main)

set_target_properties(coroutine_dojo
    PROPERTIES
    CXX_STANDARD 20)
