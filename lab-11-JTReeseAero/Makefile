all: gauss-seidel gauss-jordan

gauss-seidel: gauss_seidel.c csv/include/csv.h csv/lib/libcsv.so 
	gcc gauss_seidel.c -Wall -Lcsv/lib -Icsv/include -lcsv -lm -g -o gauss-seidel
gauss-jordan: gauss_jordan.c
	gcc -Wall gauss_jordan.c -o gauss-jordan

clean:
	rm -rf *.o
	rm gauss-seidel gauss-jordan
