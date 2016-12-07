CC=gcc
CFLAGS=-fdiagnostics-color -std=c11 -Wall
EXENAME=ACO


ACO: main.o graphFunctions.o ACO.o
	$(CC) $(CFLAGS) main.o graphFunctions.o ACO.o -o $(EXENAME)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

ACO.o: ACO.c
	$(CC) $(CFLAGS) -c ACO.c

graphFunctions.o: graphFunctions.c
	$(CC) $(CFLAGS) -c graphFunctions.c