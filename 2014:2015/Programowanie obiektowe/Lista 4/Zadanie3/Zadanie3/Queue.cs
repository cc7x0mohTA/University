// http://www.functionx.com/csharp/queues/introduction.htm

using System;
using System.Collections.Generic;

namespace Zadanie3
{
	interface IQueue<T>
	{
		int Count { get; }
		bool IsEmpty { get; }
		void Enqueue(T item);
		T Peek();
		bool Contains(T item);
		T Dequeue();
		void Clear();
		IEnumerator<T> GetEnumerator();
	}

	public class Queue<T> : IQueue<T>
	{
		private int size;
		private T[] items;

		public Queue()
		{
			size = 0;
			items = new T[10];
		}

		public int Count
		{
			get
			{
				return size;
			}
		}

		public bool IsEmpty
		{
			get
			{
				return (size == 0);
			}
		}

		public void Enqueue(T item)
		{
			items[size] = item;
			size++;
		}

		public T Peek()
		{
			if (size == 0)
				return default(T);
			return items[0];
		}

		public bool Contains(T item)
		{
			foreach (T value in items)
				if (value.Equals(item))
					return true;

			return false;
		}

		public T Dequeue()
		{
			T first = items[0];

			for (int i = 0; i < size; i++)
				items[i] = items[i + 1];
			size--;

			return first;
		}

		public void Clear()
		{
			size = 0;
		}

		public IEnumerator<T> GetEnumerator()
		{
			int counter = 0;

			while (counter < size)
			{
				yield return items[counter];
				counter++;
			}
		}

	}
}