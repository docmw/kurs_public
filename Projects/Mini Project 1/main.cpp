#include <iostream>
#include "rational.h"

using namespace std;

void rationalDemo1(){
    cout << "Rational Demo" << endl;
    Rational r2(2, 11), r3(1, -3), r5(18, 6);
    Rational res1 = 3 + r2 * r3;
    Rational res2 = (3 + r2) * r3;
    Rational res3 = 3 + r3 * (r2 + 2) / (r5 - r3);
    cout << 3 << " + " << r2 << " * " << r3 << " = " << res1 << endl;
    cout << "(" << 3 << " + " << r2 << ")" << " * " << r3 << " = " << res2
    << endl;
    cout << 3 << " + " << r3 << " * " << "(" << r2 << " + " << 2 << ")" << "/"
         << "(" << r5 << " - " << r3 << ")" << " = " << res3 << endl;
}

void rationalDemo2(){
    cout << "Write rational a (x/y):";
    Rational a{1};
    cin >> a;
    cout << "Write rational b (x/y):";
    Rational b{1};
    cin >> b;
    cout << "Write integer z:";
    int z;
    cin >> z;
    cout << endl << "a=" << a << endl;
    cout << "b=" << b << endl;
    cout << "normalized a=" << Rational::normalize(a) << endl;
    cout << "normalized b=" << Rational::normalize(b) << endl;
    cout << "a+b=" << a+b << endl;
    cout << "a-b=" << a-b << endl;
    cout << "a*b=" << a*b << endl;
    cout << "a/b=" << a/b << endl;
    cout << "a+z=" << a+z << endl;
    cout << "a-z=" << a-z << endl;
    cout << "a*z=" << a*z << endl;
    cout << "a/z=" << a/z << endl;
    cout << "z+b=" << z+b << endl;
    cout << "z-b=" << z-b << endl;
    cout << "z*b=" << z*b << endl;
    cout << "z/b=" << z/b << endl;
    if(a == b){ cout << "Rationals a and b are equal" << endl;}
    else if (a > b) {cout << "Rationals a and b are not equal, a > b" << endl;}
    else {cout << "Rationals a and b are not equal, a < b" << endl;}
    cout << "Write rational c (x/y):";
    Rational c{1};
    cin >> c;
    cout << "Write rational d (x/y):";
    Rational d{1};
    cin >> d;
    if(c >= d){ cout << "c >= d" << endl;}
    else {cout <<"c < d" << endl;}
    if(a <= d){ cout << "a <= d" << endl;}
    else {cout <<"a > d" << endl;}
}



int main()
{
    rationalDemo1();
    rationalDemo2();

    return 0;

}
