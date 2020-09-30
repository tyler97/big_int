#include "big_int.h"

int main()
{
    big_int prev(int64_t(0));
    big_int cur(int64_t(1));
    big_int fib(0);

    for (int64_t i = 1; i < int64_t(3000); ++i)
    {
        fib = cur + prev;
        prev = cur;
        cur = fib;
    }
    std::cout << fib << std::endl;

    std::cin.get();
}