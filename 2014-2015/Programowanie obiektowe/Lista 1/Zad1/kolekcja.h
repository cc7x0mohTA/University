#include <iostream>
using namespace std;
typedef int Elem;

struct Kolekcja
{
	Elem *tab;
	bool type;	// true - torba, false - zbior
	int size;
};

int rozmiar(Kolekcja *k);
int szukaj(Kolekcja *k, Elem e);
void wstaw(Kolekcja *k, Elem e);
void wypisz(Kolekcja *k);
void zbior(Kolekcja *k);
void torba(Kolekcja *k);