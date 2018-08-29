all: mult

mult: matrixmult.c csv/include/csv.h csv/lib/libcsv.so 
	gcc matrixmult.c -Wall -Lcsv/lib -Icsv/include -lcsv -o mult


clean:
	rm -rf *.o
	rm mult
