add_executable(forward_dojo dojo.cpp)
target_link_libraries(forward_dojo
    GTest::gtest GTest::gtest_main)

set_target_properties(forward_dojo
    PROPERTIES
    CXX_STANDARD 11)
