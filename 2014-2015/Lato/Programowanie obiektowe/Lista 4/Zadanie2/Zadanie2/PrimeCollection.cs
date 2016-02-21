using System;
using System.Collections;

namespace Zadanie2
{
	public class Primes : IEnumerator
	{
		private int counter;

		private bool primeCheck(int n)
		{
			if (n < 2) return false;

			for (int i = 2; i < n - 1; i++)
			{
				if (n % i == 0) return false;
			}

			return true;
		}

		public Primes ()
		{
			counter = 1;
		}
			
		public bool MoveNext ()
		{
			counter++;
			while (!primeCheck(counter)) counter++;
			return counter < int.MaxValue;
		}

		public void Reset ()
		{
			counter = 1;
		}

		public object Current
		{
			get 
			{
				return counter;
			}
		}
	}


	class PrimeCollection : IEnumerable
	{
		public IEnumerator GetEnumerator()
		{
			return new Primes();
		}
	}
}