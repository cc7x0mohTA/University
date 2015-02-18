using System;
using System.Collections;
using System.Collections.Generic;

namespace Zadanie3
{
	public class MatrixGraph : Graph
	{
		private string[] Val;
		private bool[,] Adj;
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
			rnd = new Random();
			V = numberOfVertices; E = 0;
			Val  = new string[V];
			Adj = new bool[V, V];

			for (int i = 0; i < V; i++) for(int j = 0; j < V; j++) Adj[i,j] = false;
			for(int i = 0; i < V; i++) Val[i] = i.ToString();
		}

		public MatrixGraph(int numberOfVertices = 0)
		{
			Reset (numberOfVertices);
		}

		// Generating graphs

		public void generateRandomGraph(int numberOfVertices, int numberOfEdges)
		{
			Reset(numberOfVertices);
			while (E < numberOfEdges) addRandomEdge();
		}

		public void addEdge(int v1, int v2)
		{
			Adj[v1,v2] = Adj[v2,v1] = true; E++;
		}

		public void addRandomEdge()
		{
			int a = rnd.Next (0, V), b = rnd.Next (0, V);
			if (Adj [a, b] == true) addRandomEdge ();
			else { Adj [a, b] = Adj[b,a] = true; E++; }
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

				for (int i = 0; i < V; i++)
				{
					if (Adj [u, i] == false) continue;

					int v = i;

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

			for(int i = 0; i < V; i++)
			{

				for(int j = 0; j < V; j++)
				{
					if( Adj[i, j] == false) s += "0 ";
					else s += "1 ";
				}

				s += "\n";
			}

			s += "\n"; return s;
		}

		public void print() { Console.WriteLine(toString()); }
	}
}