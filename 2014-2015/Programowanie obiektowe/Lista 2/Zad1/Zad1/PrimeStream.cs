using System;

namespace Zad1
{
	public class PrimeStream : IntStream
	{
		protected bool is_prime(int n)
		{
			if(n < 2) return false;

			for (int i = 2; i <= Math.Sqrt(n) && i < int.MaxValue; i++)
			{
				if (i == int.MaxValue)
				{
					prev = int.MaxValue;
					return false;
				}
				if (n % i == 0) return false;
			}

			return true;
		}

		public override int next()
		{
			if (prev == int.MaxValue) return -1;
			prev++;

			while (!is_prime (prev) && prev < int.MaxValue) prev++;

			if (prev == int.MaxValue) return -1;
			else return prev;
		}
	}
}