#ifndef BIG_INT_INCLUDED
#define BIG_INT_INCLUDED

#include <iostream>
#include <vector> //TODO: examine differences with using a list instead...
#include <map>
#include <utility>

#define _NODISCARD [[nodiscard]]

const std::vector<int8_t> ZERO = {0};
//const std::map<char, int8_t> CHAR_TO_INT = construct_char_map(); //Will make a copy of it..
const int8_t POSITIVE = '+';
const int8_t NEGATIVE = '-';
const uint8_t BASE_TEN = 10;

std::map<char,int8_t> construct_char_map();

class big_int{
    public:
        big_int() : num(ZERO), sign(POSITIVE) {}
        big_int(std::vector<int8_t>&& vect, const int8_t& si=POSITIVE) : num(vect), sign(si) {}
        //explicit big_int(const std::string& str, const uint8_t& base=BASE_TEN);
        //explicit big_int(std::string&& str, const uint8_t& base=BASE_TEN);
        big_int(const int64_t& number); //Will upscale if we use a smaller int value...
        big_int(const big_int& bi) : sign(bi.sign), num(bi.num) {} //copy ctor
        big_int(big_int&&) noexcept;


        big_int operator+(const big_int&) const;
        //big_int operator-(const big_int&) const;

        big_int& operator=(const big_int&);
        big_int& operator=(big_int&&) noexcept;
        bool operator==(const big_int&);

        friend std::ostream& operator<<(std::ostream&,const big_int&);
            
    private: 
        std::vector<int8_t> num; //vector that contains the large integer Example: num = [1,0,0,0,1]
        int8_t sign;
        static const std::map<char, int8_t> CHAR_TO_INT;

        big_int plus(const big_int&) const;
        //big_int minus(const big_int&) const;

        static std::pair<int8_t, int8_t> add_with_carry(const int8_t&,const int8_t&,const int8_t&); //adds 2 numbers taking in to account previous carry
        static void check_base(const std::string& str, const uint8_t base=BASE_TEN); //throws exception if str is not in base
        static int8_t get_sign(const int64_t& number);
        static int8_t get_sign(const std::string& str);

};

#endif