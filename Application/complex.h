#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <cmath>
#include <QString>

using namespace std;


class complex
{
    static QChar SEPARATOR;

    double re, im;
public:
    complex();
    complex(double, double);
    complex(const QByteArray&);

    complex operator*(complex);
    complex operator+(complex);
    complex operator-(complex);
    complex operator-();
    complex operator=(int);
    complex operator/(int);


   //complex operator-(complex);
    bool operator<(complex);
    bool operator>(complex);
    friend complex sqrt (complex);
    friend ostream& operator<<(ostream&, complex);
    friend istream& operator>>(istream&, complex&);
    friend QString& operator<< (QString&, complex);
    friend QByteArray& operator>>(QByteArray&,complex&);

    operator QString ();

};

#endif // COMPLEX_H
