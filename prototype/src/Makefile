create: create_main.c frame compress
	gcc -o create create_main.c
frame: hiddenfile.c decompress.c decompress_main.c
	gcc -o frame hiddenfile.c decompress.c decompress_main.c -lbz2
compress: compress_main.c hidefile.c compress.c
	gcc -o compress compress_main.c hidefile.c compress.c -lbz2
clean:
	rm -f compress frame create