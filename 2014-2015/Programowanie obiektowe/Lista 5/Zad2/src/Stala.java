public class Stala implements Wyrazenie
{
	int val;
	
	public Stala(int x) { val = x; }
	public int Oblicz() { return val; }
	public String toString() { return "" + val; }
}