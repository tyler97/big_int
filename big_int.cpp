#include "big_int.h"

std::map<char, int8_t> construct_char_map()
{
    int8_t count(0);
    std::map<char, int8_t> char_to_int;

    for (char ch('0'); ch <= '9'; ++ch)
    {
        char_to_int[ch] = count;
        ++count;
    }

    for (char ch('A'); ch <= 'Z'; ++ch)
    {
        char_to_int[ch] = count;
        ++count;
    }

    for (char ch('a'); ch <= 'z'; ++ch)
    {
        char_to_int[ch] = count;
        ++count;
    }

    return char_to_int;

}

const std::map<char,int8_t> big_int::CHAR_TO_INT = construct_char_map(); //initializing char conversion map...

/*TODO string constructors
big_int::big_int(const std::string& str, const uint8_t& base)
{
    
}

big_int::big_int(std::string&& str, const uint8_t& base)
{   
    
} */

big_int::big_int(const int64_t& number)
{
    sign = get_sign(number);
    if (number == 0)
    {
        num = ZERO;
    }
    else
    {
        //extracting digits with modulo operator
        int64_t temp(std::abs(number));
        while (temp >= 1)
        {
            int8_t left_over(temp % BASE_TEN);
            temp /= BASE_TEN;
            num.push_back(left_over);
        }

        std::reverse(num.begin(), num.end());
    }

}

big_int::big_int(big_int&& bi) noexcept
{
    sign = bi.sign;
    num = std::move(bi.num);
}

big_int& big_int::operator=(const big_int& bi)
{
    if (this == &bi)//same memory address, same object
    {
        return *this;
    }

    sign = bi.sign;
    num = bi.num;
    
    return *this;

}

big_int& big_int::operator=(big_int&& bi) noexcept
{
    sign = bi.sign;
    num = std::move(bi.num);
    return *this;
}

bool big_int::operator==(const big_int& bi)
{
    if(sign != bi.sign or num.size() != bi.num.size())
    {
        return false;
    }

    for (size_t i(0); i < num.size(); ++i)
    {
        if (num[i] != bi.num[i])
        {
            return false;
        }
    }
    return true;
}

big_int big_int::operator+(const big_int& right_val) const
{
    return plus(right_val);
}

// For now only implementing positive integers
big_int big_int::plus(const big_int& right_val) const
{
    int64_t left_index(num.size() - 1); //TODO: Encapsulate length in a function of the class.
    int64_t right_index(right_val.num.size() - 1);

    std::vector<int8_t> sum_vect;
    int8_t carry(0);

    while(left_index >= 0 && right_index >= 0)
    {
        std::pair<int8_t,int8_t> sum_carry = add_with_carry(num[left_index--], right_val.num[right_index--], carry);
        sum_vect.push_back(sum_carry.first);
        carry = sum_carry.second; 
    }

    //check for remaining elements
    while (left_index >= 0)
    {
        std::pair<int8_t,int8_t> sum_carry = add_with_carry(num[left_index--], 0, carry);
        sum_vect.push_back(sum_carry.first);
        carry = sum_carry.second;
    }

    while (right_index >= 0)
    {
        std::pair<int8_t,int8_t> sum_carry = add_with_carry(right_val.num[right_index--], 0, carry);
        sum_vect.push_back(sum_carry.first);
        carry = sum_carry.second;
    }

    if(carry)
    {
        sum_vect.push_back(carry);
    }

    std::reverse(sum_vect.begin(), sum_vect.end());
    big_int myInt(std::move(sum_vect));
    return myInt;
}

//TODO
/*big_int big_int::minus(const big_int& right_val) const
{
    
}*/

std::pair<int8_t, int8_t> big_int::add_with_carry(const int8_t& val_1, const int8_t& val_2, const int8_t& prev_carry)
{
    int8_t sum(0), carry(0);
    sum = val_1 + val_2 + prev_carry;
    
    if(sum > 9) //there's been a carry
    {
        carry = 1;
        sum %= 10;
    }

    return {sum, carry};

}

int8_t big_int::get_sign(const int64_t& number)
{
    if(number < 0)
    {
        return NEGATIVE;
    }
    return POSITIVE;
}

int8_t big_int::get_sign(const std::string& str)
{
    if(*str.begin() == NEGATIVE)
    {
        return NEGATIVE;
    }
    return POSITIVE;
}

void big_int::check_base(const std::string& str, const uint8_t base)
{
    for(const char& ch : str)
    {
        auto iter(CHAR_TO_INT.find(ch));

        if(iter == CHAR_TO_INT.end())
        {
            throw std::exception("big_int: unexpected symbol");
        }
        else if(iter->second >= base)
        {
            throw std::exception("big_int: string not in correct base");
        }
    }
}

std::ostream& operator<<(std::ostream& os, const big_int& bi)
{
    for (const int8_t& i : bi.num)
    {
        os << static_cast<int32_t>(i); //for printing number instead of char
    }
    return os;
}