#include <iostream>
#include <array>
#include <ranges>
#include <fmt/ranges.h>

// 9:18 of Moar Functional with C++23 - Björn Fahller - code::dive 2023
// https://youtu.be/CVBlYvTenVo?si=YYeuuWZa1ZGXM8Ks&t=558

using namespace std::views;

auto apply = []<typename F>(F&& f) {
    return [f = std::forward<F>(f)]<typename T>(T&& t) {
        return std::apply(f, std::forward<T>(t));
    };
};

template <size_t ... Is>
auto swizzle = []<typename F>(F&& f) {
    return [f = std::forward<F>(f)]<typename ... Ts>(Ts&& ... ts)
    requires ((Is < sizeof...(ts)) && ...)
    {
        auto tup = std::forward_as_tuple(std::forward<Ts>(ts)...);
        return f(std::get<Is>(std::move(tup))...);
    };
};

int main() {

    auto const sequence = std::array{1,3,8,2,3,8,1};
    auto const deltas   = sequence 
                        | pairwise_transform(swizzle<1,0>(std::minus{}));

    fmt::print("{}\n", deltas);
    
    return 0;
}
