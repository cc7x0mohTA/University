package Zad1;

public abstract class TopologicalSpace implements Comparable<TopologicalSpace>
{
	public String Name;
	
	public abstract double SeparationAxiomNumber();
	
	public int compareTo(TopologicalSpace TS)
	{
		if(TS.SeparationAxiomNumber() == this.SeparationAxiomNumber()) return 0;
		else if(TS.SeparationAxiomNumber() < this.SeparationAxiomNumber()) return 1;
		else return -1;
	}
	
	public String toString() {
        return "Given topological space " + Name + ". It's T" + SeparationAxiomNumber() + "\n";
    }
}