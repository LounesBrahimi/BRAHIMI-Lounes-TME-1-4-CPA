run : executable
	./executable
compiler : main.o page_rank.o draw.o
	gcc -o executable main.o page_rank.o draw.o
executable : main.o page_rank.o draw.o
	gcc -o executable main.o page_rank.o draw.o
page_rank.o : page_rank.c
	gcc -o page_rank.o -c page_rank.c
draw.o : draw.c page_rank.h
	gcc -o draw.o -c draw.c
main.o : main.c draw.h
	gcc -o main.o -c main.c
clean : 
	rm main.o draw.o page_rank.o executable

