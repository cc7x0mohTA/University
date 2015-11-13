using System;
using System.Collections.Generic;

namespace Zad4
{
	class ListaLeniwa
	{
		protected int sz;
		protected List<int> L;
		private Random r;

		protected virtual int kolejnaLiczba(int n)
		{
			return r.Next ();
		}

		public int size()
		{
			return sz;
		}

		public int element(int n)
		{
			if (n < sz) return L [n];
			else
			{
				sz = n;

				if (L.Count == 0) L.Add (0);

				for(int i = L.Count-1; i < n; i++)
				{
					L.Add(kolejnaLiczba(L[i]));
				}

				return L [n];
			}
		}

		public void wypisz()
		{
			System.Console.WriteLine("Rozmiar listy to " + sz);
		}

		public ListaLeniwa()
		{
			sz = 0;
			L = new List<int>();
			r = new Random ();
		}
	}
}