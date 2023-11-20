CC=gcc --std=c99 -g
EXE=run

all: main.c dir.o functions.o hash.o
	$(CC) main.c dir.o functions.o hash.o -o $(EXE)

dir.o: dir.c dir.h
	$(CC) -c dir.c

functions.o: functions.c functions.h
	$(CC) -c functions.c

hash.o: hash.c hash.h
	$(CC) -c hash.c

clean: 
	rm -f *.o $(EXE)