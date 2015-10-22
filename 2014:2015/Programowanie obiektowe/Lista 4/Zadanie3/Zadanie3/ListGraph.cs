using System;
using System.Collections.Generic;
using System.Collections;

namespace Zadanie3
{
	public class ListGraph : Graph
	{
		private List<int>[] L;
		private string[] Val;
		private Random rnd;
		private int V, E;

		// Getters:

		public int getV()
		{
			return V;
		}

		public int getE()
		{
			return E;
		}

		// Constructors:

		private void Reset(int numberOfVertices)
		{
			V = numberOfVertices; E = 0;
			Val  = new string[V];
			L = new List<int>[V];

			for(int i = 0; i < V; i++) Val[i] = i.ToString();
			for (int i = 0; i < V; i++) L[i] = new List<int> ();
		}

		public ListGraph(int numberOfVertices = 0)
		{
			rnd = new Random(DateTime.Now.Millisecond);
			Reset(numberOfVertices);
		}

		// Generating graphs

		public void generateRandomGraph(int numberOfVertices, int numberOfEdges)
		{
			Reset(numberOfVertices);
			while (E < numberOfEdges) addRandomEdge();
		}

		public void addEdge(int v1, int v2)
		{
			L[v1].Add(v2); L[v2].Add(v1); E++;
		}

		public void addRandomEdge()
		{
			int a = rnd.Next (0, V); int b = rnd.Next(0, V);
			addEdge(a, b);
		}

		// Shortest paths :

		public int shortestPath(int a, int b)
		{
			Zadanie3.Queue<int> Q = new Queue<int>();
			bool[] Viz = new bool[V];
			int[] Dist = new int[V];
			string[] Path = new string[V];

			for (int i = 0; i < V; i++)
			{
				Viz [i] = false;
				Dist [i] = int.MaxValue;
				Path [i] = "";
			}

			Q.Enqueue (a);  Viz[a] = true; Dist [a] = 0; Path [a] = a.ToString() + " ";

			while (Q.Count > 0)
			{
				int u = Q.Dequeue();

				for (int i = 0; i < L [u].Count; i++)
				{
					int v = L [u][i];

					if (Viz[v] == false)
					{
						Q.Enqueue (v); Viz [v] = true;
						Dist [v] = Dist [u] + 1;
						Path [v] = Path [u] + "-> " + v.ToString () + " ";
					}
				}
			}

			Console.WriteLine (Path [b]);
			return Dist[b];
		}


		// Printing etc.

		public string toString()
		{
			string s = "";

			for (int i = 0; i < V; i++)
			{
				s += i.ToString () + ": ";

				for(int j = 0; j < L[i].Count; j++) s += L[i][j].ToString() + ", ";

				s += "\n";
			}

			return s;
		}

		public void print() { Console.WriteLine(toString()); }
	}
}