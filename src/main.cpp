#include "big_int.h"

int main()
{
    big_int prev = 0;
    big_int cur = 1;
    big_int fib;
    
    for (int64_t i = 1; i < int64_t(3000); ++i)
    {
        fib = cur + prev;
        prev = cur;
        cur = fib;
    }
    std::cout << fib << std::endl;

    std::cin.get();
}