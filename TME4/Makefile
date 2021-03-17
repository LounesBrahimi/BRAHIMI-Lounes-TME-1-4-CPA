run : executable
	./executable
compiler : main.o k_core_decomposition.o tas_binaire.o
	gcc -o executable main.o k_core_decomposition.o tas_binaire.o
executable : main.o k_core_decomposition.o tas_binaire.o
	gcc -o executable main.o k_core_decomposition.o tas_binaire.o
tas_binaire.o : tas_binaire.c
	gcc -o tas_binaire.o -c tas_binaire.c
k_core_decomposition.o : k_core_decomposition.c tas_binaire.h
	gcc -o k_core_decomposition.o -c k_core_decomposition.c
main.o : main.c k_core_decomposition.h
	gcc -o main.o -c main.c
clean :
	rm main.o k_core_decomposition.o tas_binaire.o executable
