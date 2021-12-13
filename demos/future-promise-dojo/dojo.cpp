#include <future>

#include <gtest/gtest.h>

int costly_square(int const x) {
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    return x * x;
}

TEST(FUTURE_PROMISE, futureByAsync) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::future<int> future = std::async(costly_square, 10);

    std::cout << future.get() << std::endl;
}

TEST(FUTURE_PROMISE, futureByPromise) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::promise<int> promise;
    std::future<int> future = promise.get_future();
    auto td = std::thread([&promise]() {
        promise.set_value(costly_square(10));
    });

    std::cout << future.get() << std::endl;
    td.join();
}

TEST(FUTURE_PROMISE, futureByPackage) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto task = std::packaged_task<int(int)>(costly_square);
    std::future<int> future = task.get_future();

    task(10);

    std::cout << future.get() << std::endl;
}
