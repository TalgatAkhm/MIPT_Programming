//
// Created by talgat on 10.12.17.
//
#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::string;
using std::ostream;
using std::istream;
using std::pair;
//using std::


class BigInteger
{
public:

    BigInteger() :
            digits(1, 0),
            is_positive_or_zero(true)
    {}

    BigInteger(const int &another)
    {
        if (another != 0)
        {
            is_positive_or_zero = another > 0;
            int abs_another = absolute_int(another);
            while (abs_another)
            {
                digits.emplace_back(abs_another % 10);
                abs_another /= 10;
            }
        }
        else
        {
            is_positive_or_zero = true;
            digits.push_back(0);
        }
    }

    BigInteger(const string &another)
    {
        if (another[0] == '-')
        {
            is_positive_or_zero = false;
            for (int i = another.size() - 1; i >= 1; --i)
                digits.emplace_back(another[i] - '0');
        }
        else
        {
            is_positive_or_zero = true;
            for (int i = another.size() - 1; i >= 0; --i)
                digits.emplace_back(another[i] - '0');
        }
    }


    BigInteger &plus_equals(BigInteger &first, const BigInteger &second);

    BigInteger &mult_equals(BigInteger &first, const BigInteger &second);

    BigInteger &div_equals(BigInteger &first, const BigInteger &second);

    BigInteger &div_equals(BigInteger &first, int second);

    const BigInteger operator-() const;


    BigInteger &operator++();

    const BigInteger operator++(int);

    BigInteger operator--();

    const BigInteger operator--(int);

    string toString() const;

    explicit operator bool() const;

    //pair<BigInteger, BigInteger> div_mod(const BigInteger &a, const BigInteger &b);


    friend std::ostream &operator<<(std::ostream &stream,BigInteger const  &show)
    {
        return stream<<show.toString();
    }

    friend std::istream &operator>>(std::istream& stream, BigInteger& input)
    {
        std::string s;
        stream>>s;

        input = BigInteger(s);
        return stream;
    }

    bool is_positive() const;
private:
    vector<char> digits;
    bool is_positive_or_zero;



    bool is_negative() const;

    void check_for_zero();

    void delete_extra_zeros();

    BigInteger absolute(const BigInteger &bigInteger);

    int absolute_int(const int &a);
};

BigInteger &operator+=(BigInteger &first, const BigInteger &another);

BigInteger &operator*=(BigInteger &first, const BigInteger &another);

BigInteger &operator-=(BigInteger &first, const BigInteger &another);

const BigInteger operator+(const BigInteger &first, const BigInteger &second);

const BigInteger operator-(const BigInteger &first, const BigInteger &second);

const BigInteger operator*(const BigInteger &first, const BigInteger &second);

BigInteger& operator/=(BigInteger& first, const BigInteger& second);

BigInteger& operator/=(BigInteger& first, int second);

const BigInteger operator/(const BigInteger& first, const BigInteger& second);

BigInteger& operator%=(BigInteger& first, const BigInteger& second);

const BigInteger operator%(const BigInteger& first, const BigInteger& second);

bool operator==(const BigInteger& first, const BigInteger &second);

bool operator!=(const BigInteger& first, const BigInteger &second);

bool operator>(const BigInteger& first, const BigInteger &second);

bool operator<(const BigInteger& first, const BigInteger &second);

bool operator>=(const BigInteger& first, const BigInteger &second);

bool operator<=(const BigInteger& first, const BigInteger &second);
