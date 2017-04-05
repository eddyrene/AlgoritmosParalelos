#
CC = mpicc
#
all: blocksends brecv nbrecv

blocksends:  blocksends.c newsleep.o
	$(CC) -o blocksends blocksends.c newsleep.o

brecv:  brecv.c newsleep.o
	$(CC) -o brecv brecv.c newsleep.o

nbrecv:  nbrecv.c newsleep.o
	$(CC) -o nbrecv nbrecv.c newsleep.o

newsleep.o:  newsleep.c
	$(CC) -c newsleep.c

clean:
	rm *.o
