#include <gtest/gtest.h>

#include <experimental/coroutine>


template <typename T>
struct generator {
    struct promise_type;
    using handle_type = std::experimental::coroutine_handle<promise_type>;

    handle_type coro;

    explicit generator(handle_type h) : coro(h) {}
    ~generator() {
        if (coro) coro.destroy();
    }

    generator(generator const&) = delete;
    generator& operator=(generator const&) = delete;
    generator(generator&& other) noexcept : coro(other.coro) {
        other.coro = nullptr;
    }
    generator& operator=(generator&& other) noexcept {
        coro = other.coro;
        other.coro = nullptr;
        return *this;
    }

    T getValue() {
        return coro.promise().current_value;
    }

    bool next() {
        coro.resume();
        return not coro.done();
    }

    struct promise_type {
        promise_type() = default;
        ~promise_type() = default;

        [[maybe_unused]] auto initial_suspend() {
            return std::experimental::suspend_always();
        }

        [[maybe_unused]] auto final_suspend() noexcept {
            return std::experimental::suspend_always();
        }

        [[maybe_unused]] auto get_return_object() {
            return generator{handle_type::from_promise(*this)};
        }

        [[maybe_unused]] auto return_void() {
            return std::experimental::suspend_never();
        }

        [[maybe_unused]] auto yield_value(T const value) {
            current_value = value;
            return std::experimental::suspend_always();
        }

        [[maybe_unused]] void unhandled_exception() {
            std::exit(-1);
        }

        T current_value;
    };

};


generator<int> range(int const begin, int const end, int const inc = 1) {
    for (auto i = begin; i <= end; i += inc) {
        co_yield i;
    }
}

TEST(COROUTINE, generaterByCoYield) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto gen = range(10, 20);
    while (gen.next()) {
        std::cout << gen.getValue() << " ";
    }
    std::cout << std::endl;
}
