#include <iostream>
#include <array>
#include <ranges>
#include <https://raw.githubusercontent.com/codereport/blackbird/main/combinators.hpp>
#include <fmt/ranges.h>

// 9:18 of Moar Functional with C++23 - Björn Fahller - code::dive 2023
// https://youtu.be/CVBlYvTenVo?si=YYeuuWZa1ZGXM8Ks&t=558

using namespace combinators;
using namespace std::views;

int main() {

    auto const sequence = std::array{1,3,8,2,3,8,1};
    auto const deltas   = sequence 
                        | pairwise_transform(_c(std::minus{}));

    fmt::print("{}\n", deltas);
    
    return 0;
}
