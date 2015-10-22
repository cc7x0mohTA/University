using System;

namespace Zad1
{
	public class RandomStream : IntStream
	{
		Random rnd = new Random();

		public override int next()
		{
			return rnd.Next();
		}
	}
}

