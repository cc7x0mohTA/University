#include "complex.h"

Complex Dodaj(Complex A, Complex B)
{
	Complex C;
	C.Re = A.Re + B.Re;
	C.Im = A.Im + B.Im;
	return C;
}

void Dodaj(Complex *A, Complex B)
{
	A->Re = A->Re + B.Re;
	A->Im = A->Im + B.Im;
}

Complex Odejmij(Complex A, Complex B)
{
	Complex C;
	C.Re = A.Re - B.Re;
	C.Im = A.Im - B.Im;
	return C;
}

void Odejmij(Complex *A, Complex B)
{
	A->Re = A->Re - B.Re;
	A->Im = A->Im - B.Im;
}

Complex Pomnoz(Complex A, Complex B)
{
	Complex C;
	C.Re = A.Re * B.Re - A.Im * B.Im;
	C.Im = A.Im * B.Re + A.Re * B.Im;
	return C;
}

void Pomnoz(Complex *A, Complex B)
{
	double X = A->Re * B.Re - A->Im * B.Im;
	double Y = A->Im * B.Re + A->Re * B.Im;
	A->Re = X; A->Im = Y;
}

Complex Podziel(Complex A, Complex B)
{
	Complex C;
	double a = A.Re, b = A.Im, c = B.Re, d = B.Im;
	double e = c*c+d*d;

	C.Re = (a*c+b*d)/e;
	C.Im = (b*c-a*d)/e;
	return C;
}

void Podziel(Complex *A, Complex B)
{
	double a = A->Re, b = A->Im, c = B.Re, d = B.Im;
	double e = c*c+d*d;

	A->Re = (a*c+b*d)/e;
	A->Im = (b*c-a*d)/e;
}

void Wypisz(Complex *A)
{
	cout << A->Re << " + " << A->Im << "i.\n";
}