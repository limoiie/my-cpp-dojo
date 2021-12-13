add_executable(concepts_dojo dojo.cpp)
target_link_libraries(concepts_dojo
    GTest::gtest GTest::gtest_main)

set_target_properties(concepts_dojo
    PROPERTIES
    CXX_STANDARD 20)
