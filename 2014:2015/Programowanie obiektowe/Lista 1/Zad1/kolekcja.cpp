#include "kolekcja.h"
using namespace std;

typedef int Elem;

int rozmiar(Kolekcja *k)
{
	return k->size;
}

int szukaj(Kolekcja *k, Elem e)
{
	int counter = 0;

	for(int i = 0; i < k->size; i++)
	{
		if(e == k->tab[i]) counter++;
	}

	return counter;
}

void wstaw(Kolekcja *k, Elem e)
{
	if(k->type == false)	// to jest zbior
	{
		for(int i = 0; i < k->size; i++)
		{
			if(k->tab[i] == e) return;
		}
	}

	Elem *T = new Elem[k->size+1];

	for(int i = 0; i < k->size; i++) T[i] = (k->tab[i]);

	T[k->size] = e; k->size++; delete[] k->tab; k->tab = T;
}

void wypisz(Kolekcja *k)
{
	for(int i = 0; i < k->size; i++)
	{
		cout << k->tab[i] << "\n";
	}
}

void zbior(Kolekcja *k)
{
	k->type = false;
	k->size = 0;
	k->tab = new Elem[1];
}

void torba(Kolekcja *k)
{
	k->type = true;
	k->size = 0;
	k->tab = new Elem[1];
}