using System;

namespace Zad1
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			IntStream I = new IntStream();

			System.Console.WriteLine ("IntStream\n");

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine (I.next ());
				System.Console.WriteLine (I.eos ());
			}

			System.Console.WriteLine ("\nPrimeStream\n");

			PrimeStream J = new PrimeStream();

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine (J.next ());
				System.Console.WriteLine (J.eos ());
			}

			System.Console.WriteLine ("\nRandomWordStream\n");

			RandomWordStream K = new RandomWordStream();

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine (K.next ());
				System.Console.WriteLine (K.eos ());
			}

			System.Console.WriteLine ("\nRandomStream\n");

			RandomStream L = new RandomStream();

			for (int i = 0; i < 10; i++)
			{
				System.Console.WriteLine (L.next ());
				System.Console.WriteLine (L.eos ());
			}
		}
	}
}