#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational
{
public:
    Rational(int numerator, int denominator = 1);
    ~Rational() {}
    Rational(const Rational& copy);
    Rational& operator=(Rational const& other);
    Rational& operator=(int i);
    int numerator() const { return numer; }
    int denominator() const { return denom; }
    static Rational normalize(Rational const& other);
    static Rational normalized(int numerator, int denominator);
    Rational operator+(Rational const& other) const;
    Rational operator-(Rational const& other) const;
    Rational operator*(Rational const& other) const;
    Rational operator/(Rational const& other) const;
    Rational operator+() const;
    Rational operator-() const;
    bool operator==(Rational const& other) const;
    bool operator>=(Rational const& other) const;
    bool operator<=(Rational const& other) const;
    bool operator>(Rational const& other) const;
    bool operator<(Rational const& other) const;
private:
    int numer;
    int denom;
    int gcdND;
    void initialize(int numerator, int denominator);
    friend std::ostream& operator<<(std::ostream &, const Rational &);
    friend std::istream& operator>>(std::istream &, Rational &);
};
Rational operator+(Rational const& r, int i);
Rational operator+(int i, Rational const& r);
Rational operator-(Rational const& r, int i);
Rational operator-(int i, Rational const& r);
Rational operator*(Rational const& r, int i);
Rational operator*(int i, Rational const& r);
Rational operator/(Rational const& r, int i);
Rational operator/(int i, Rational const& r);

#endif
