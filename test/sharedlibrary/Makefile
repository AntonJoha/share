sharedflags= -c -Os -fPIC
prog: main.o ltest.so
	gcc -Os -W -z max-page-size=0x1000 -o prog main.o  ltest.so
main.o: main.c hiddenfile.h
	gcc -c -Os -W -z max-page-size=0x1000 main.c
ltest.so: hiddenfile.o decompress.o
	gcc -Os -shared -o ltest.so hiddenfile.o decompress.o -lbz2
hiddenfile.o: hiddenfile.c hiddenfile.h 
	gcc $(sharedflags) hiddenfile.c
decompress.o: decompress.c compression.h 
	gcc $(sharedflags) decompress.c
clean:
	rm -f *.so
	rm -f *.o
	rm -f prog