prog: decompress.o filehandling.o main.o
	gcc -o test decompress.o filehandling.o main.o -lbz2
decompress.o: decompress.c compression.h
	gcc -c decompress.c
filehandling.o: filehandling.c compression.h filehandling.h
	gcc -c filehandling.c 
main.o: main.c filehandling.h compression.h
	gcc -c main.c