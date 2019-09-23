#include "rational.h"
#include <iostream>
#include <string>
#include "math.h"
using std::cout;
using std::endl;

Rational::Rational(int numerator, int denominator)
{
    initialize(numerator, denominator);
}


Rational::Rational(const Rational& copy) {initialize(copy.numer, copy.denom);}
Rational& Rational::operator=(const Rational& copy)
{

    if(&copy != this){
        this->numer = copy.numer;
        this->denom = copy.denom;
    }
    return *this;
}



Rational& Rational::operator=(int i){
    this->numer = i;
    this->denom = 1;
    return *this;
}

Rational Rational::normalize(Rational const& other){
    int x = abs(other.numer);
    int y = abs(other.denom);
    while(y != 0){ //Euclidean algorithm
        int tmp = y;
        y = x%y;
        x = tmp;
    }
    return Rational{(other.numer/x), (other.denom/x)};
}

Rational Rational::normalized(int nominator, int denominator){


    return Rational::normalize(Rational{nominator, denominator});
}



Rational Rational::operator+(Rational const& other) const{
    int num = (this->numer)*(other.denom) + (this->denom)*(other.numer);
    int denom = (this->denom)*(other.denom);
    return normalized(num, denom);
}

Rational Rational::operator-(Rational const& other) const{
    int num = (this->numer)*(other.denom) - (this->denom)*(other.numer);
    int denom = (this->denom)*(other.denom);
    return normalized(num, denom);
}

Rational Rational::operator*(Rational const& other) const{
    int num = (this->numer)*(other.numer);
    int denom = (this->denom)*(other.denom);
    return normalized(num, denom);
}

Rational Rational::operator/(Rational const& other) const{
    int num = (this->numer)*(other.denom);
    int denom = (this->denom)*(other.numer);
    return normalized(num, denom);
}

Rational Rational::operator+() const{
    return normalize(*this+Rational(1,1));
}

Rational Rational::operator-() const{
    return normalize(*this-Rational(1,1));
}

bool Rational::operator==(Rational const& other) const{
    Rational x = (*this / other);
    if (x.numer == 1 && x.denom == 1){return true;}
    else {return false;}


}

bool Rational::operator>=(Rational const& other) const{
    Rational x = (*this - other);
    if (x.numer >= 0){return true;}
    else {return false;}
}

bool Rational::operator<=(Rational const& other) const{
    Rational x = (*this - other);
    if (x.numer <= 0){return true;}
    else {return false;}
}

bool Rational::operator>(Rational const& other) const{
    Rational x = (*this - other);
    if (x.numer > 0){return true;}
    else {return false;}
}

bool Rational::operator<(Rational const& other) const{
    Rational x = (*this - other);
    if (x.numer < 0){return true;}
    else {return false;}
}




Rational operator+(Rational const& r, int i){
    return Rational::normalize(r + Rational(i/1));
}

Rational operator+(int i, Rational const& r){
    return Rational::normalize(r + Rational(i/1));
}

Rational operator-(Rational const& r, int i){
    return Rational::normalize(r - Rational(i/1));
}

Rational operator-(int i, Rational const& r){
    return Rational::normalize(Rational(i/1) - r);
}

Rational operator*(Rational const& r, int i){
    return Rational::normalize(r * Rational(i/1));
}

Rational operator*(int i, Rational const& r){
    return Rational::normalize(r * Rational(i/1));
}

Rational operator/(int i, Rational const& r){
    return Rational::normalize(Rational(i/1) / r);
}

Rational operator/(Rational const& r, int i){
    return Rational::normalize(r / Rational(i/1));
}

std::ostream& operator<<(std::ostream &os, const Rational &other){
    if(other.denom == 1){os << other.numer;}
    else if(other.numer < 0){
        os << "(" << other.numer << "/" << other.denom << ")";
    }
    else {
        os << other.numer << "/" << other.denom;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Rational &other){
    std::string stream;
    std::getline(is, stream, '/');
    other.numer = std::stoi(stream);
    int y = 0;
    is>>y;
    while(y == 0){
      cout << endl << "Y cannot be equal 0! Please write Y again:";
      is>>y;


    }

    other.denom = y;

    return is;
}

void Rational::initialize(int numerator, int denominator){


    if(denominator == 0){
        cout << "denominator cannot be equal 0! setting denominator to 1" << endl;
        numer = numerator;
        denom = 1;
    }
    else if (denominator < 0){
        numer = -numerator;
        denom = -denominator;
    }
    else {
        numer = numerator;
        denom = denominator;
    }
}
