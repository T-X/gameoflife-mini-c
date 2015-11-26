HEADERS = gol.h gol_test.h

all: gol

gol_test.o: gol_test.c $(HEADERS)
gol.o: gol.c $(HEADERS)

gol: gol.o gol_test.o

clean:
	rm -f gol gol.o gol_test.o
