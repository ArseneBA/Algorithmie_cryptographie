CC=gcc
CFLAGS=-I. -g

%.o: %.C
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o nus.o test.o
	$(CC) -o main main.o nus.o test.o

clean:
	rm -f *.o main

run : main
	./$<