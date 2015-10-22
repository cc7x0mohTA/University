using System;

namespace Zad1
{
	static class RandomLetter
	{
		static Random _random = new Random();

		public static char GetLetter()
		{
			int num = _random.Next(0, 26);
			char let = (char)('a' + num);
			return let;
		}
	}
}