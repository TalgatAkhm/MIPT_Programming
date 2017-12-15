//
// Created by talgat on 10.12.17.
//

#include "BigInteger.h"

int BigInteger::absolute_int(const int &digits)
{
    if (digits > 0)
        return digits;
    else
        return -digits;
}

string BigInteger::toString() const
{
    string sbigint = "";
    if ((!is_positive_or_zero) && *this)
        sbigint += "-";

    for (int i = (int)digits.size() - 1; i >= 0; --i)
        sbigint += '0' + digits[i];

    return sbigint;
}

BigInteger::operator bool() const
{
    return digits[digits.size() - 1] != 0;
}

bool BigInteger::is_positive() const
{
    return is_positive_or_zero && *this;
}


const BigInteger BigInteger::operator-() const
{
    BigInteger change_sign(*this);
    if (change_sign)
        change_sign.is_positive_or_zero = !is_positive_or_zero;
    return change_sign;
}


BigInteger &operator+=(BigInteger &first, const BigInteger &another)
{
    return first.plus_equals(first, another);
}

void BigInteger::delete_extra_zeros()
{
    while (digits.size() > 1 && digits.back() == 0)
        digits.pop_back();
}

const BigInteger operator+(const BigInteger &first, const BigInteger &another)
{
    BigInteger temp(first);
    return temp += another;
}

const BigInteger operator-(const BigInteger &first, const BigInteger &second)
{
    BigInteger temp(first);
    return temp -= second;
}

BigInteger BigInteger::absolute(const BigInteger &bigInteger)
{
    BigInteger res(bigInteger);
    res.is_positive_or_zero = true;
    return res;
}

BigInteger &BigInteger::operator++()
{
    return (*this += 1);
}


const BigInteger BigInteger::operator++(int)
{
    BigInteger res = *this;
    *this += 1;
    return res;
}

BigInteger BigInteger::operator--()
{
    return (*this -= 1);
}


const BigInteger BigInteger::operator--(int)
{
    BigInteger res = *this;
    *this -= 1;
    return res;
}


BigInteger &operator-=(BigInteger &first, const BigInteger &another)
{
    return first += (-another);
}

BigInteger &operator*=(BigInteger &first, const BigInteger &another)
{
    return first.mult_equals(first, another);
}

bool operator==(const BigInteger &first, const BigInteger &second)
{
    return !(first - second);
}


bool operator>(const BigInteger &first, const BigInteger &second)
{
    return (first - second).is_positive();
}

bool operator<(const BigInteger &first, const BigInteger &second)
{
    return (second - first).is_positive();
}


bool operator!=(const BigInteger &first, const BigInteger &second)
{
    return !(first == second);
}


bool operator>=(const BigInteger &first, const BigInteger &second)
{
    return !(first < second);
}

bool operator<=(const BigInteger &first, const BigInteger &second)
{
    return !(first > second);
}


const BigInteger operator*(const BigInteger &first, const BigInteger &second)
{
    BigInteger temp(first);
    return temp *= second;
}

bool BigInteger::is_negative() const
{
    return !is_positive_or_zero;
}

void BigInteger::check_for_zero()
{
    if (!*this)
        is_positive_or_zero = false;
}

BigInteger &BigInteger::div_equals(BigInteger &first, const BigInteger &second)
{
    if(absolute(first).digits.size() < absolute(second).digits.size())
    {
        first = 0;
        return first;
    }

    if (!second)
        return first;

    bool res_sign = !(first.is_positive_or_zero ^ second.is_positive_or_zero);
    first.is_positive_or_zero = true;

    BigInteger another_copy(absolute(second));
    BigInteger place_factor(1);

    while (another_copy.digits.size() < first.digits.size())
    {
        another_copy *= 10;
        place_factor *= 10;
    }

    BigInteger res(0);

    while (another_copy)
    {
        while (first >= another_copy)
        {
            first -= another_copy;
            res += place_factor;
        }
        another_copy /= 10;
        place_factor /= 10;
    }

    res.is_positive_or_zero = res_sign;
    first.digits.resize(0);
    return first = res;
}

BigInteger &operator/=(BigInteger &first, const BigInteger &second)
{
    return first.div_equals(first, second);
}

BigInteger &BigInteger::div_equals(BigInteger &first, int a)
{
    BigInteger res;
    res.digits = std::vector<char>(first.digits.size(), 0);
    res.is_positive_or_zero = !(first.is_positive_or_zero ^ (a >= 0));
    int a_copy(absolute_int(a));
    int appendage(0);

    for (int i = static_cast<int>(first.digits.size() - 1); i >= 0; --i)
    {
        int current_digit = first.digits[i] + appendage * 10;

        res.digits[i] = static_cast<char>(current_digit / a_copy);
        appendage = current_digit % a_copy;
    }
    res.delete_extra_zeros();
    return first = res;
}

BigInteger &operator/=(BigInteger &first, int a)
{
    return first.div_equals(first, a);
}


const BigInteger operator/(const BigInteger &first, const BigInteger &second)
{
    BigInteger temp(first);
    return temp /= second;
}


BigInteger &operator%=(BigInteger &first, const BigInteger &second)
{
    return first = first - first / second * second;
}



const BigInteger operator%(const BigInteger &first, const BigInteger &second)
{
    BigInteger temp(first);
    return temp %= second;
}

BigInteger &BigInteger::plus_equals(BigInteger &first, const BigInteger &second)
{
    int appendage = 0;

    const unsigned long biggest_size = std::max(first.digits.size(), second.digits.size());
    for (int i = 0; i < (int)biggest_size || appendage != 0; ++i)
    {
        if (i == (int)first.digits.size())
            first.digits.push_back(0);


        const char this_sign = static_cast<char>(first.is_positive_or_zero ? 1 : -1);
        const char another_sign = static_cast<char>(second.is_positive_or_zero ? 1 : -1);

        int i_less = i < (int)second.digits.size() ? second.digits[i] * this_sign * another_sign : 0;

        first.digits[i] += appendage + i_less;

        appendage = (first.digits[i] >= 10 ? 1 : 0);
        if (appendage)
            first.digits[i] -= 10;
    }

    first.delete_extra_zeros();

    if (first.digits.back() < 0)
    {
        first.is_positive_or_zero = !first.is_positive_or_zero;
        for (int i = 0; i < (int)first.digits.size(); ++i)
            first.digits[i] *= -1;
    }

    for (int i = 0; i < (int)first.digits.size() - 1; ++i)
        if (first.digits[i] < 0)
        {
            first.digits[i] += 10;
            --first.digits[i + 1];
        }

    first.delete_extra_zeros();

    return first;
}

BigInteger &BigInteger::mult_equals(BigInteger &first, const BigInteger &second)
{
    BigInteger mult;
    mult.digits = vector<char>(first.digits.size() + second.digits.size(), 0);

    mult.is_positive_or_zero = !(first.is_positive_or_zero ^ second.is_positive_or_zero);

    for (int i = 0; i < static_cast<int>(first.digits.size()); ++i)
        for (int j = 0, appendage = 0; j < (int)second.digits.size() || appendage != 0; ++j)
        {
            int j_less = j < (int)second.digits.size() ? second.digits[j] : 0;

            char current_digit = static_cast<char>(mult.digits[i + j] + first.digits[i] * j_less + appendage);

            mult.digits[i + j] = static_cast<char>(current_digit % 10);
            appendage = current_digit / 10;
        }
    mult.delete_extra_zeros();
    first = mult;


    return first;
}


