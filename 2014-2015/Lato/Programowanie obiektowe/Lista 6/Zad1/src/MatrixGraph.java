import java.io.File;
import java.io.Serializable;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import java.util.Scanner;

public class MatrixGraph implements Serializable
{

	private static final long serialVersionUID = 1L;
	
	private String[] Val;
	private Boolean [][] Adj;
	private Random rnd;
	private int V, E;

	// Getters:

	public int getV() { return V; }
	public int getE() { return E; }

	// Constructors:
		
	private void Reset(int numberOfVertices)
	{
		rnd = new Random();
		V = numberOfVertices; E = 0;
		Val  = new String[V];
		Adj = new Boolean [V][V];

		for (int i = 0; i < V; i++) for(int j = 0; j < V; j++) Adj[i][j] = false;
		for(int i = 0; i < V; i++) Val[i] = Integer.toString(i);
	}

	public MatrixGraph() { Reset(0); }
	
	public MatrixGraph(int numberOfVertices) { Reset (numberOfVertices); }

	// Generating graphs

	public void generateRandomGraph(int numberOfVertices, int numberOfEdges)
	{
		Reset(numberOfVertices);
		while (E < numberOfEdges) addRandomEdge();
	}

	public void addEdge(int v1, int v2)
	{
		Adj[v1][v2] = Adj[v2][v1] = true; E++;
	}

	public void addRandomEdge()
	{
		int a = rnd.nextInt(V), b = rnd.nextInt(V);
		if (Adj [a][b] == true) addRandomEdge ();
		else { Adj [a][b] = Adj[b][a] = true; E++; }
	}

	// Shortest paths :

	public int shortestPath(int a, int b)
	{
		Queue<Integer> Q = new LinkedList<Integer>();
		Boolean[] Viz = new Boolean[V];
		int[] Dist = new int[V];
		String[] Path = new String[V];

		for (int i = 0; i < V; i++)
		{
			Viz [i] = false;
			Dist [i] = Integer.MAX_VALUE;
			Path [i] = "";
		}

		Q.add(a);  Viz[a] = true; Dist [a] = 0; Path [a] = Integer.toString(a) + " ";

		while (Q.size() > 0)
		{
			int u = Q.poll();

			for (int i = 0; i < V; i++)
			{
				if (Adj [u][i] == false) continue;

				int v = i;

				if (Viz[v] == false)
				{
					Q.add(v); Viz [v] = true;
					Dist [v] = Dist [u] + 1;
					Path [v] = Path [u] + "-> " + Integer.toString(v) + " ";
				}
			}
		}

		System.out.println(Path [b]);
		return Dist[b];
	}

	// Printing etc.

	public String toString()
	{
		String s = "";

		for(int i = 0; i < V; i++)
		{

			for(int j = 0; j < V; j++)
			{
				if( Adj[i][j] == false) s += "0 ";
				else s += "1 ";
			}

			s += "\n";
		}

		s += "\n"; return s;
	}

	public void print() { System.out.println(toString()); }
	
	public void WriteToFile() throws FileNotFoundException
	{
		PrintWriter zapis = new PrintWriter("graph.txt");
		
		zapis.println(Integer.toString(V));
		zapis.println(toString());
		zapis.close();
	}
	
	public void LoadFromFile(String FileName) throws FileNotFoundException
	{
	      File file = new File(FileName);
	      Scanner in = new Scanner(file);
	      String zdanie = in.nextLine();
	      
	      System.out.println(file.getParent());
	      
	      V = Integer.parseInt(zdanie); Reset(V);
	      
	      for(int i = 0; i < V; i++)
	      {
	    	  zdanie = in.nextLine();	    	  
	    	  
	    	  String[] T = zdanie.split(" ");
	    	  
	    	  for(int j = 0; j < V; j++)
	    	  {
	    		  int val = Integer.parseInt(T[j]);
	    		  if(val == 1) this.addEdge(i, j);
	    	  }
	      }
	      
	      in.close();
	}
}