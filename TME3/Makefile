run : executable
	./executable
compiler : main.o label_propagation.o hierarchique.o bechmark.o
	gcc -o executable main.o label_propagation.o hierarchique.o bechmark.o
executable : main.o label_propagation.o hierarchique.o bechmark.o
	gcc -o executable main.o label_propagation.o hierarchique.o bechmark.o
bechmark.o : bechmark.c
	gcc -o bechmark.o -c bechmark.c
label_propagation.o : label_propagation.c bechmark.h
	gcc -o label_propagation.o -c label_propagation.c
hierarchique.o : hierarchique.c label_propagation.h
	gcc -o hierarchique.o -c hierarchique.c
main.o : main.c label_propagation.h hierarchique.h
	gcc -o main.o -c main.c
clean :
	rm main.o hierarchique.o label_propagation.o bechmark.o executable
