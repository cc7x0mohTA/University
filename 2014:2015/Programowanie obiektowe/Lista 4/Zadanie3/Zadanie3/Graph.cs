using System;

namespace Zadanie3
{
	interface Graph	// Assume that it's acyclic graph
	{
		void generateRandomGraph(int numberOfVertices, int numberOfEdges);
		int shortestPath(int v1, int v2);
		void addEdge(int v1, int v2);
		string toString();
		void print();
	}
}