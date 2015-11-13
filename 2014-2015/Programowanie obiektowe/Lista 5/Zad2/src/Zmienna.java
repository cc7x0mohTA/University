import java.util.*;

public class Zmienna implements Wyrazenie
{
	String s; Hashtable<String, Integer> Tree;
	
	public Zmienna(String s, Hashtable<String, Integer> l)
	{
		this.s = s; this.Tree = l;
	}
	
	public int Oblicz() { return Tree.get(s); }
	public String toString() { return s; }
}