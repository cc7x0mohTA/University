CC = gcc
CFLAGS = -std=gnu99 -Wall -Wextra -pthread

prog: prog.c
	$(CC) $(CFLAGS) prog.c -o prog -lrt 

clean:
	rm *.o prog
