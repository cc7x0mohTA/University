package Zad1;

class Collection<V, T extends Comparable<T>>
{
	V val; T key;
	Collection<V, T> next;
	
	public Collection(V val, T key)
	{
		this.val = val; this.key = key; this.next = null;
	}

	public Collection() {}
	
	public Collection<V, T> Pop()
	{
		Collection<V, T> wsk = this.next;
		if(this.next != null) this.next = this.next.next;
		return wsk;
	}
	
	public void Push(V val, T key)
	{
		if(this.next != null)
		{
			if (this.next.key.compareTo(key)>=0)
			{
 				Collection<V,T> k=this.next;
 				this.next=new Collection<V,T>(val, key);
 				this.next.next=k;
			}
			else this.next.Push(val, key);
		}
		else this.next=new Collection<V,T>(val, key);
	}
	
	public void PrintAll()
	{
 		if (this.next != null)
 		{
 			System.out.println("[ " + this.next.val + " " + this.next.key + " ]");
 			this.next.PrintAll();
 		}
 	}
}