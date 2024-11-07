#include "polinome.h"
#include <math.h>

Polinome::Polinome()
{
    N = 0;
    mode = PrintModeClassic;
}

Polinome::Polinome(number new_an, number new_roots[], int new_size)
{
    N = new_size;
    roots.change_size(N);
    coefficents.change_size(N + 1);

    for (int i = 0; i < N; i++)
    {
        roots[i] = new_roots[i];
    }

    count_coefficents(new_an);
    mode = PrintModeClassic;
}

void Polinome::count_coefficents(number new_an)
{
    for (int i = 0; i < N; i++)
        coefficents[i] = 0;
    coefficents[N] = new_an;
    coefficents[1] = number (1, 0);
    coefficents[0] = -roots[0];

    for (int k = 2; k <= N; k++)
    {
        coefficents[k] = coefficents[k-1];
        for (int i = k-1; i > 0; i--)
        {
            coefficents[i] = coefficents[i-1] - coefficents[i] * roots[k-1];
        }
        coefficents[0] = -coefficents[0] * roots[k-1];
    }
    for (int i = 0; i <= N; i++)
        coefficents[i] = coefficents[i] * new_an;
}

void Polinome::change_print_mode (PrintMode new_mode)
{
    mode = new_mode;
}

ostream& operator<< (ostream& os, Polinome& pol)
{
    if (pol.mode == PrintModeCanonic)
    {
        for (int i = pol.N; i > 0; i--)
            os << pol.coefficents[i] << " x^" << i << " + ";
        os << pol.coefficents[0] << std::endl;
    }
    else
    {
        os << pol.coefficents[pol.N] << " * ";
        for (int i = 0; i < pol.N - 1; i++)
            os << "(x - " << pol.roots[i] << ") * ";
        os << "(x - " << pol.roots[pol.N - 1] << ")" << std::endl;
    }
    return os;
}

QString& operator<< (QString& os, Polinome& pol)
{
    if (pol.mode == PrintModeCanonic)
    {
        for (int i = pol.N; i > 0; i--)
        {
            os << pol.coefficents[i];
            os += " x^";
            os += QString().setNum(i);
            os += " + ";
        }
        os << pol.coefficents[0];
        os += "\n";
    }
    else
    {
        os << pol.coefficents[pol.N];
        os += " * ";
        for (int i = 0; i < pol.N - 1; i++)
        {
            os += "(x - ";
            os << pol.roots[i];
            os +=  ") * ";
        }
        os += "(x - ";
        os << pol.roots[pol.N - 1];
        os += ")";
        os += "\n";
    }
    return os;
}

istream& operator>> (istream& is, Polinome& pol)
{
    is >> pol.coefficents[pol.N];
    for (int i = 0; i < pol.N; i++)
        is >> pol.roots[i];
    pol.count_coefficents(pol.coefficents[pol.N]);
    return is;
}

number Polinome::count_val (number new_point)
{
    number val = coefficents[N];
    for (int i = 0; i < N; i++)
        val = (new_point - roots[i]) * val;
    return val;
}

void Polinome::change_an(number new_an)
{
    coefficents[N] = new_an;
    count_coefficents(coefficents[N]);
}

void Polinome::change_roots(number new_root, int new_index)
{
    roots[new_index] = new_root;
    count_coefficents(coefficents[N]);
}

void Polinome::change_size(int new_size)
{
    //number an = coefficents[N];
    roots.change_size(new_size);
    coefficents.change_size(new_size + 1);
    N = new_size;
    //change_an(an);
}

int Polinome::get_size()
{
    return N;
}
