#include <iostream>
#include "kolekcja.h"
using namespace std;

int main()
{
	cout << "\nTorba:\n";

	Kolekcja K; torba(&K);

	for(int i = 0; i < 10; i++) wstaw(&K, i+1);
	for(int i = 0; i < 5; i++) wstaw(&K, i+1);

	wypisz(&K);
	cout << "Szukam 5 jest ich : " << szukaj(&K, 55) << "\n";
	cout << "Teraz jest " << rozmiar(&K) << " elementow.\n";

	cout << "\nZbior:\n";

	Kolekcja L; zbior(&K);

	for(int i = 0; i < 10; i++) wstaw(&L, i+1);
	for(int i = 0; i < 5; i++) wstaw(&L, i+1);

	wypisz(&L);
	cout << "Szukam 5 jest ich : " << szukaj(&L, 5) << "\n";
	cout << "Teraz jest " << rozmiar(&L) << " elementow.\n";


	return 0;
}