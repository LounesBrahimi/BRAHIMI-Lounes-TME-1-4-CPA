run : executable
	./executable
compiler : main.o lower_bound.o upper_bound.o triangle.o adjmatrix.o listedges.o exercice1.o adjarray.o fifo.o
	gcc -o executable main.o lower_bound.o upper_bound.o triangle.o adjmatrix.o listedges.o exercice1.o adjarray.o fifo.o
executable : main.o lower_bound.o upper_bound.o triangle.o adjmatrix.o listedges.o exercice1.o adjarray.o fifo.o
	gcc -o executable main.o lower_bound.o upper_bound.o triangle.o adjmatrix.o listedges.o exercice1.o adjarray.o fifo.o
fifo.o: fifo.c
	gcc -o fifo.o -c fifo.c
exercice1.o: exercice1.c
	gcc -o exercice1.o -c exercice1.c
listedge.o: listedge.c
	gcc -o listedge.o -c listedge.c
adjmatrix.o : adjmatrix.c listedges.h
	gcc -o adjmatrix.o -c adjmatrix.c
adjarray.o : adjarray.c adjmatrix.h
	gcc -o adjarray.o -c adjarray.c
triangle.o : triangle.c adjarray.h
	gcc -o triangle.o -c triangle.c
lower_bound.o : lower_bound.c adjarray.h fifo.h
	gcc -o lower_bound.o -c lower_bound.c
upper_bound.o : upper_bound.c lower_bound.h
	gcc -o upper_bound.o -c upper_bound.c
main.o : main.c exercice1.h lower_bound.h upper_bound.h triangle.h
	gcc -o main.o -c main.c
clean : 
	rm main.o fifo.o executable upper_bound.o lower_bound.o triangle.o adjarray.o adjmatrix.o listedges.o exercice1.o
