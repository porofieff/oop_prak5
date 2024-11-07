#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include "number.h"

using namespace std;

class Array
{
    number* arr;
    int size;

public:
    Array();
    Array(int);

    int sizeo();

    friend istream& operator >> (istream&, Array&);
    friend ostream& operator << (ostream&, Array&);

    void change_size(int);
    void change_element(int, number);

    number calculate_arefmetic_avarage();
    number calculate_square();
    number& operator[](int);

    void qsort(bool);

    ~Array();

};

#endif // ARRAY_H
