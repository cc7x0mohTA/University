import java.util.Hashtable;

public class Main
{
	public static void main(String[] args)
	{
		Hashtable<String, Integer> Drzewko = new Hashtable<String, Integer>();
		Drzewko.put("x",2);
		System.out.println("x = " + Drzewko.get("x"));
		Drzewko.put("y",4);
		System.out.println("y = " + Drzewko.get("y"));

		Wyrazenie napis = new Dodaj(new Stala(2), new Zmienna("x", Drzewko));
		napis = new Pomnoz(new Stala(7), napis);
		napis = new Podziel(napis, new Zmienna("y", Drzewko));
		napis = new Odejmij(napis, new Stala(1));
		System.out.println(napis.toString() + " = " + napis.Oblicz());
	}
}