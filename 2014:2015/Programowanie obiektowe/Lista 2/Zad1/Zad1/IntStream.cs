using System;

namespace Zad1
{
	public class IntStream
	{
		protected int prev;

		public virtual int next()
		{
			if (prev == int.MaxValue) return -1;
			prev++; return prev;
		}

		public bool eos()
		{
			return (prev == int.MaxValue);
		}

		public void reset()
		{
			prev = -1;
		}

		public IntStream()
		{
			reset();
		}
	}
}