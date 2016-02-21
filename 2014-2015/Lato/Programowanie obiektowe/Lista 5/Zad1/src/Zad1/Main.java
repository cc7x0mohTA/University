package Zad1;
import java.awt.List;
import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class Main
{
	public static void main(String[] args)
	{
        System.out.println("Hierarchia Klas.");
        ArrayList<TopologicalSpace> TS = new ArrayList<TopologicalSpace>();
        
		TS.add(new TychonoffSpace("A"));
		TS.add(new UrysohnSpace("B"));
		TS.add(new KolmogorovSpace("C"));
		TS.add(new FrechetSpace("J"));
		
		Collections.sort(TS);		
        for(TopologicalSpace t : TS) System.out.println(t);
	}
}