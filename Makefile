default : copper.o

copper.make : copper.pl
	./copper.pl makefile testexamples.c >$@

clean :
	- rm -f copper.make 

include copper.make
