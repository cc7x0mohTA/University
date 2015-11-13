import java.io.FileNotFoundException;

public class Main
{
	public static void main(String[] args) throws FileNotFoundException
	{		
		MatrixGraph G = new MatrixGraph();
		
		try {
			G.LoadFromFile("/Users/bartoszbednarczyk/Desktop/Lista6Zad1/graph.txt");
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		G.print();
	}
}
