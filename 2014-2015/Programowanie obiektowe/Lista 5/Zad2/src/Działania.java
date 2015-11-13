class Dodaj implements Wyrazenie 
{
	Wyrazenie a;
	Wyrazenie b;
	
	public Dodaj (Wyrazenie a, Wyrazenie b) { this.a = a; this.b = b; }
	public int Oblicz() { return a.Oblicz() + b.Oblicz(); }
	public String toString() { return "(" + a + "+" + b + ")"; }	
}

class Odejmij implements Wyrazenie 
{
	Wyrazenie a;
	Wyrazenie b;
	
	public Odejmij (Wyrazenie a, Wyrazenie b) { this.a = a; this.b = b; }
	public int Oblicz() { return a.Oblicz() - b.Oblicz(); }
	public String toString() { return "(" + a + "-" + b + ")"; }	
}

class Podziel implements Wyrazenie 
{
	Wyrazenie a;
	Wyrazenie b;
	
	public Podziel (Wyrazenie a, Wyrazenie b) { this.a = a; this.b = b; }
	public int Oblicz() { return a.Oblicz() / b.Oblicz(); }
	public String toString() { return "(" + a + "/" + b + ")"; }	
}

class Pomnoz implements Wyrazenie 
{
	Wyrazenie a;
	Wyrazenie b;
	
	public Pomnoz (Wyrazenie a, Wyrazenie b) { this.a = a; this.b = b; }
	public int Oblicz() { return a.Oblicz() * b.Oblicz(); }
	public String toString() { return "(" + a + "*" + b + ")"; }	
}