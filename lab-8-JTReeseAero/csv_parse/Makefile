all: csvfix csvtest csvvalid csvinfo

csvfix: tools/csvfix.c include/csv.h
	gcc tools/csvfix.c -lcsv -Iinclude -Llib -o bin/csvfix

csvtest: tools/csvtest.c include/csv.h
	gcc tools/csvtest.c -lcsv -Iinclude -Llib -o bin/csvtest

csvvalid: tools/csvvalid.c include/csv.h
	gcc tools/csvvalid.c -lcsv -Iinclude -Llib -o bin/csvvalid

csvinfo: tools/csvinfo.c include/csv.h 
	gcc tools/csvinfo.c -lcsv -Iinclude -Llib -o bin/csvinfo
