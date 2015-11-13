using System;

namespace Zad1
{
	public class RandomWordStream : PrimeStream
	{
		public new string next()
		{
			if (prev == int.MaxValue) return "";
			prev++;

			while (!is_prime (prev) && prev < int.MaxValue) prev++;

			if (prev == int.MaxValue) return "";
			else
			{
				string s = "";

				for (int i = 0; i < prev; i++)
				{
					s += RandomLetter.GetLetter();
				}

				return s;
			}
		}
	}
}