#include <iostream>
#include <array>
#include <ranges>

// 9:18 of Moar Functional with C++23 - Björn Fahller - code::dive 2023
// https://youtu.be/CVBlYvTenVo?si=YYeuuWZa1ZGXM8Ks&t=558

int main() {
    std::array sequence{1,3,8,2,3,8,1};

    for (auto d : sequence
                | std::ranges::views::pairwise
                | std::ranges::views::transform(
                    [](auto&& t) { auto&& [a,b] = t; return b - a; }
                  ))
    {
        std::cout << d << ' ';
    }

    return 0;
}
