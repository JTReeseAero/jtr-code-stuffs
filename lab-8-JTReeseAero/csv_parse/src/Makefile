all: ../bin/csv2matrix
../bin/csv2matrix: csv2matrix.c ../include/csv.h ../lib/libcsv.so
	gcc -Wall csv2matrix.c -lcsv -I../include -L../lib -o ../bin/csv2matrix
clean: 
	rm -rf *.o
	rm ../bin/csv2matrix
