#ifndef CHISL_H
#define CHISL_H

#include <QTextStream>
#include <cmath>

inline int countik(int num)
{
    if (num == 0) return 1;
    int count = 0;
    while (num != 0) {
        count++;
        num /= 10;
    }
    return count;
}
inline int sumdig(int num, int power)
{
    int sum = 0;
    while (num != 0) {
        int digit = num % 10;
        sum += pow(digit, power);
        num /= 10;
    }
    return sum;
}

class chisl
{
    int x;
    int y;
public:
    chisl() : x(1), y(1) {}
    chisl(int a) : x(a), y(a) {}
    chisl(int a, int b) : x(a), y(b) {}
    chisl(const chisl& a) : x(a.x), y(a.y) {}

    chisl& operator=(const chisl& a)
    {
        if (this != &a)
        {
            x = a.x;
            y = a.y;
        }
        return *this;
    }

    int nod()
    {
        int a = x, b = y;
        while (a != 0 && b != 0)
        {
            if (a > b)
                a %= b;
            else
                b %= a;
        }
        return a + b;
    }
    int nok()
    {
        int n = nod();
        if (n == 0) return 0;
        return std::abs(x * y) / n;
    }
    int prostx()
    {
        if (x < 2) return 0;
        for (int i = 2; i <= sqrt(x); i++)
        {
            if (x % i == 0)
                return 0;
        }
        return x;
    }
    int prosty()
    {
        if (y < 2) return 0;
        for (int i = 2; i <= sqrt(y); i++)
        {
            if (y % i == 0)
                return 0;
        }
        return y;
    }
    bool isarmstrongx()
    {
        if (x < 0) return false;
        int dig = countik(x);
        int sum = sumdig(x, dig);
        return sum == x;
    }
    bool isarmstrongy()
    {
        if (y < 0) return false;
        int dig = countik(y);
        int sum = sumdig(y, dig);
        return sum == y;
    }

    friend QTextStream& operator<<(QTextStream& os, const chisl& c)
    {
        os << c.x << " " << c.y;
        return os;
    }
    friend QTextStream& operator>>(QTextStream& is, chisl& c)
    {
        is >> c.x >> c.y;
        return is;
    }
};

#endif // CHISL_H
