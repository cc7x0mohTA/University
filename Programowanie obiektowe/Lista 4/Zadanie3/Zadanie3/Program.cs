using System;

namespace Zadanie3
{
	class MainClass
	{
		public static void TestListGraph()
		{
			Console.WriteLine ("LIST GRAPH :\n"); 
			ListGraph G = new ListGraph (7);

			G.addEdge (1, 2);
			G.addEdge (2, 3);
			G.addEdge (2, 4);
			G.addEdge (2, 5);
			G.addEdge (5, 6);

			G.print ();

			Console.WriteLine (G.shortestPath (1, 6));
			Console.WriteLine ("END OF LIST GRAPH\n"); 
		}

		public static void TestMatrixGraph()
		{
			Console.WriteLine ("MATRIX GRAPH :\n"); 
			MatrixGraph G = new MatrixGraph (6);

			G.addEdge (0, 1);
			G.addEdge (1, 2);
			G.addEdge (1, 3);
			G.addEdge (1, 4);
			G.addEdge (4, 5);

			G.print ();

			Console.WriteLine (G.shortestPath (0, 5));
			Console.WriteLine ("END OF Matrix GRAPH\n"); 
		}

		public static void Main (string[] args)
		{
			TestListGraph ();
			TestMatrixGraph ();
		}
	}
}