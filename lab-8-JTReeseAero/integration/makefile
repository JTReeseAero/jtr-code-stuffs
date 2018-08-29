all: a.out 
a.out: main.o libintegration.so func_test.o
	gcc main.o libintegration.so func_test.o -L. -lm -lcsv -L../csv_parse/lib  
main.o: main.c integration.h
	gcc -I . -c main.c
func_test.o: func_test.c
	gcc -c  func_test.c
clean:
	rm -rf *.o
	rm a.out
