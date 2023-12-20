I really enjoyed this talk by Björn Fahller but I really wished he had mentioned a couple things. This repo is the code that I will use in a YouTube video.

[![image](https://github.com/codereport/moar_functional_fahller/assets/36027403/736803e3-6987-4634-a66e-9d90c3c550ad)
)](https://www.youtube.com/embed/CVBlYvTenVo?si=c3Io0y8q_MuEXH1A&amp;start=558)

|       |               Change                |             Godbolt             |
| :---: | :---------------------------------: | :-----------------------------: |
|   0   |              Original               | https://godbolt.org/z/navP7h7de |
|   1   |         Original + Swizzle          | https://godbolt.org/z/5Yzafqne5 |
|   2   | Formatting + `const` + `fmt::print` | https://godbolt.org/z/4Gjjq76jv |
|   3   |        `pairwise_transform`         | https://godbolt.org/z/GK1effY77 |
|   4   |         C Combinator (`_c`)         | https://godbolt.org/z/EehTP56K4 |
|   5   |               `_sub_`               | https://godbolt.org/z/s9EG4YE6M |

We refactor:

```cpp
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
```
to
```cpp
using namespace combinators;
using namespace std::views;

int main() {

    auto const sequence = std::array{1,3,8,2,3,8,1};
    auto const deltas   = sequence 
                        | pairwise_transform(_c(_sub_));

    fmt::print("{}\n", deltas);
    
    return 0;
}
```
