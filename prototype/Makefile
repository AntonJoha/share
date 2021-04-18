elfcomp: elfcomp
	(cd src/ && make)
	mkdir -p bin
	cp src/create bin/elfcomp
	cp src/frame bin/frame
	cp src/compress bin/compress
clean: 
	(cd src/ && make clean)
	rm -f elfcomp
