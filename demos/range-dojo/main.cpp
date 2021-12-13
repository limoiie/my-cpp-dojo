#include <iostream>
#include <vector>

#include <ranges>


int main() {
    std::vector<int> const ints = {0, 1, 2, 3, 4};
    auto even = [](int i) { return 0 == i %2; };
    auto square = [](int i) { return i * i; };

    auto a = std::ranges::filter_view(ints, even);

    for (auto i : ints | std::views::filter(even) | std::views::transform(square)) {
        std::cout << "hello, world" << std::endl;
    }
    return 0;
}