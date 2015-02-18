#include <iostream>
#include "complex.h"
using namespace std;

int main()
{
	Complex A; A.Re = 2; A.Im = 5;
	Complex C; C.Re = 3; C.Im = 1;

	Complex B = Dodaj(A,C); Wypisz(&B);
	B = Odejmij(A,C); Wypisz(&B);
	B = Pomnoz(A,C); Wypisz(&B);

	return 0;
}