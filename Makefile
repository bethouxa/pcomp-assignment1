CC=gcc
CFLAGS=-fdiagnostics-color -std=gnu11 -Wall
LIBS=-pthread
DEBFLAGS=-g3 -pg
RELEASEFLAGS=-O3
EXENAME=ACO


ACO: main.o graphFunctions.o ACO.o
	$(CC) $(CFLAGS) $(LIBS) main.o graphFunctions.o ACO.o -o $(EXENAME)

debug: main.o graphFunctions.o ACO.o
	$(CC) $(CFLAGS) $(DEBFLAGS) $(LIBS) main.o graphFunctions.o ACO.o -o $(EXENAME)

release: main.o graphFunctions.o ACO.o
	$(CC) $(CFLAGS) $(RELEASEFLAGS) $(LIBS) main.o graphFunctions.o ACO.o -o $(EXENAME)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ACO.o: ACO.c
	$(CC) $(CFLAGS) -c ACO.c

graphFunctions.o: graphFunctions.c
	$(CC) $(CFLAGS) -c graphFunctions.c

clean:
	rm -f $(EXENAME) *.o a.out
