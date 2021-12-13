cmake_minimum_required(VERSION 3.20)
project(dojo)

find_package(GTest CONFIG REQUIRED)

add_subdirectory(demos/concepts-dojo)
add_subdirectory(demos/coroutine-dojo)
add_subdirectory(demos/forward-dojo)
add_subdirectory(demos/functional-dojo)
add_subdirectory(demos/future-promise-dojo)
add_subdirectory(demos/range-dojo)