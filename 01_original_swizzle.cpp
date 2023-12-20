#include <iostream>
#include <array>
#include <ranges>

// 9:18 of Moar Functional with C++23 - Björn Fahller - code::dive 2023
// https://youtu.be/CVBlYvTenVo?si=YYeuuWZa1ZGXM8Ks&t=558

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
    std::array sequence{1,3,8,2,3,8,1};

    for (auto d : sequence
                | std::ranges::views::pairwise
                | std::ranges::views::transform(
                    apply(swizzle<1,0>(std::minus{}))
                  ))
    {
        std::cout << d << ' ';
    }

    return 0;
}
