public class Main
{

	public static void main(String[] args)
	{
		int[] T = {4,2,1,5,6};

        MergeSort sort = new MergeSort(T, 0, 5); sort.start();
        
        try
        {
        	sort.join();
        }
        catch(Exception e) {}

        for(int i = 0; i < 5; i++) System.out.println(T[i]);
	}
}