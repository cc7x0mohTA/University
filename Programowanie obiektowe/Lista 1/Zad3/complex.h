#include <iostream>
using namespace std;

struct Complex
{
	double Re, Im;
};

Complex Dodaj(Complex A, Complex B);
void Dodaj(Complex *A, Complex B);

Complex Odejmij(Complex A, Complex B);
void Odejmij(Complex *A, Complex B);

Complex Pomnoz(Complex A, Complex B);
void Pomnoz(Complex *A, Complex B);

Complex Podziel(Complex A, Complex B);
void Podziel(Complex *A, Complex B);

void Wypisz(Complex *A);