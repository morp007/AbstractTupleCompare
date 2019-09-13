/*
* This is an open source non-commercial project. Dear PVS-Studio, please check it.
* PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
*/

#include <array>
#include <chrono>
#include <iostream>
#include <memory>


namespace
{
enum CompareRes
{
    LT = 0,
    GT,
    EQ,
};


template<typename T>
CompareRes compare(const T &x, const T &y)
{
    if (x < y)
        return CompareRes::LT;
    else if (x > y)
        return CompareRes::GT;

    return CompareRes::EQ;
}


template<typename T>
CompareRes l45_abstractCompare(const T &x, const T &y)
{
    if (x.size() != y.size())
    {
        std::cout << "throw" << std::endl;
        throw;
    }

    for (auto i = x.size(); i > 0; i--)
    {
        const auto index = i - 1;
        const auto res = compare(x[index], y[index]);

        if (res != CompareRes::EQ)
        {
            return res;
        }
    }

    return CompareRes::EQ;
}


#define START(n)                                             \
    const auto start_##n = std::chrono::steady_clock::now();

#define END(n)                                                                          \
    const auto end_##n = std::chrono::steady_clock::now();                              \
    const auto diff_##n = end_##n - start_##n;                                          \
    std::cout << std::chrono::duration<double, std::milli>(diff_##n).count() << " ms"   \
              << std::endl;
}  // end of unnamed namespace


int main(const int /*argc*/, const char *const /*argv*/[])
{
    std::cout << "LT: " << LT << std::endl
              << "GT: " << GT << std::endl
              << "EQ: " << EQ << std::endl
              << std::endl;

    using Arr = std::array<size_t, 100000000>;
    auto a = std::make_unique<Arr>();
    auto b = std::make_unique<Arr>();

    for (size_t i = 0; i < a->size(); i++)
    {
        (*a)[i] = (*b)[i] = i + 1;
    }

    START(1)
    const auto res = l45_abstractCompare(*a, *b);
    END(1)

    std::cout << "--- result: " << res << std::endl;

    return 0;
}


#undef END
#undef START
