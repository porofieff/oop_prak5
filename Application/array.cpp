#include "array.h"
#include <math.h>

// ToDO
//не работает сравнение чисел
//нужео сделать корень числа
//почемуто возникает ошибка и программа не отрабатывает 5 и 6 кейсы

Array::Array()
{
    arr = nullptr;
    size = 0;
}

int Array::sizeo()
{
    return size;
}
Array::Array(int numb)
{
    number* arr2 = new number[numb];
    arr = arr2;
    size = numb;
}

istream& operator >> (istream& is, Array& a)
{
    for (int i = 0; i < a.size; i++)
    {
        is>>a.arr[i];
    }
    return is;
}

ostream& operator << (ostream& os, Array& a)
{
    for (int i = 0; i < a.size; i++)
    {
        os<<a.arr[i]<<" ";
    }
    os << endl;
    return os;
}

void Array::change_size(int new_size)
{
    number* arr2 = new number[new_size];
    if (new_size > size)
    {
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i];
    }
    else
    {
        for (int i = 0; i < new_size; i++)
            arr2[i] = arr[i];
    }
    if(arr != nullptr)
        delete[] arr;
    arr = arr2;
    size = new_size;
}


number& Array::operator[](int i)
{
    return arr[i];
}

number Array::calculate_arefmetic_avarage()
{
    number avg;
    for (int i = 0; i < size; i++)
    {
        avg = avg + arr[i];
    }
    return avg/size;
}

number Array::calculate_square()
{
    number avg = calculate_arefmetic_avarage();
    number sum_dif;
    for (int i = 0; i < size; i++)
    {
        sum_dif = sum_dif + (avg-arr[i])*(avg-arr[i]);
    }
    number average_square = sqrt((sum_dif/(size-1)));
    return average_square;
}

void Array::qsort(bool reverse)
{
    for (int i = 0; i < size-1; i++)
    {
        for(int j = 0; j < size-1; j++)
        {
            if(!reverse)
            {
                if(arr[j] > arr[j+1])
                {
                    number temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
            else
            {
                if(arr[j] < arr[j+1])
                {
                    number temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }
}

void Array::change_element(int index, number elem)
{
    arr[index] = elem;
}

Array::~Array()
{
    if(arr != nullptr)
        delete[] arr;
}
