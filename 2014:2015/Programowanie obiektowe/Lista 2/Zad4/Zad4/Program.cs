using System;

namespace Zad4
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			Console.WriteLine ("\nLista zwykla :\n");

			ListaLeniwa lista = new ListaLeniwa();
			lista.wypisz ();
			Console.WriteLine ("50 element listy to " + lista.element (50));
			lista.wypisz();
			Console.WriteLine ("52 element listy to " + lista.element(52));
			lista.wypisz();
			Console.WriteLine ("2 element listy to " + lista.element(2));
			lista.wypisz();
			Console.WriteLine ("100 element listy to " + lista.element(100));
			lista.wypisz();	

			Console.WriteLine ("\nLista pierwsza :\n");

			Pierwsze lista2 = new Pierwsze();
			lista2.wypisz ();
			Console.WriteLine ("50 element listy to " + lista2.element (50));
			lista2.wypisz();
			Console.WriteLine ("52 element listy to " + lista2.element(52));
			lista2.wypisz();
			Console.WriteLine ("2 element listy to " + lista2.element(2));
			lista2.wypisz();
			Console.WriteLine ("100 element listy to " + lista2.element(100));
			lista2.wypisz();
			Console.WriteLine ("1 element listy to " + lista2.element(1));
			lista2.wypisz();
		}
	}
}