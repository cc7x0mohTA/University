#include <stdio.h>

int main()
{
	FILE *fp;
	int t0;
	int t1 = 0;
	int t2 = 0;
	int t3, t4, t5;

	fp  = fopen("plik.dat", "r");

	loop:

		t0 = fgetc(fp);
		if(t0 == -1) goto end;
		
		// war 1:

		if(t0 == 10) t3 = 1;
		else t3 = 0;

		// war 2:

		if(t1 == 1) t4 = 1;
		else t4 = 0;

		t5 = t3 & t4;

		// war 3:

		if(t5 == 1)
		{
			t2++; 
			t1 = 0;		
		}

		// war 4:

		if(t0 > 32) t1  = 1;
		
		goto loop;
	end:

	if(t1 == 1) t2++;

	printf("\nLiczba niepustych linii to : %d\n", t2);
	fclose(fp);
}
