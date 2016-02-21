import java.io.Serializable;

public class Ksiazka implements Serializable
{
	private static final long serialVersionUID = 4661681646491395516L;
	public String Tytul, autor;
	public int wydanie;
	
	public Ksiazka(String T, String a, int w)
	{
		Tytul = T; autor = a; wydanie = w;
	}
	
	public Ksiazka() { this("Tytul", "Autor", 11111); } 

	public String toString()
	{
		return Tytul + "\n" + autor + "\n" + Integer.toString(wydanie);
	}
}