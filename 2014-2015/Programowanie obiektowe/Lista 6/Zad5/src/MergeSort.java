class MergeSort extends Thread
{
    private static final int minMergeSortArraySize  =  2;

    int[] array;
    int start, end;

    public MergeSort(int[] a, int s, int e) { array = a; start = s; end = e; }

    private void merge(int[] temp)
    {
        int i1, i2, tempi;

        i1 = start;
        i2 = end / 2;
        tempi = 0;

        while (i1 < end / 2 && i2 < end) {
            if (array[i1] < array[i2])
                temp[tempi++] = array[i1++];
            else
                temp[tempi++] = array[i2++];
        }

        while (i1 < end / 2) {
            temp[tempi++] = array[i1++];
        }

        while (i2 < end) {
            temp[tempi++] = array[i2++];
        }

        System.arraycopy(array, start, temp, 0, end - start);
    }

    private void insertionSort()
    {
        for (int i = start; i < end; i++)
        {
            int j, v = array[i];

            for (j = i - 1; j >= 0; j--) {
                if (array[j] <= v)
                    break;
                array[j + 1] = array[j];
            }

            array[j + 1] = v;
        }
    }

    public void run()
    {
        int[] temp = new int[end];

        if ((end - start) < minMergeSortArraySize) {
            insertionSort();
            return;
        }

        MergeSort sort1 = new MergeSort(array, start, start + ((end-start)/2));
        MergeSort sort2 = new MergeSort(array, start + ((end-start)/2), end);

        sort1.start();
        sort2.start();
        try {
          sort1.join();
          sort2.join();
        }
        catch (Exception e) {}

        merge(temp);
    }
}