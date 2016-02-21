using System;
using System.Collections.Generic;

namespace Zad4
{
	class Pierwsze : ListaLeniwa
	{
		private bool is_prime(int n)
		{
			if(n < 2) return false;

			for (int i = 2; i <= Math.Sqrt(n); i++)
			{
				if (n % i == 0) return false;
			}

			return true;
		}

		override protected int kolejnaLiczba(int n)
		{
			n++;
			while (!is_prime (n)) n++;
			return n;
		}
	}
}