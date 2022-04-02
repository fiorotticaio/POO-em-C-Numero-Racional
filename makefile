prog: clean main.o
	gcc -o prog main.o numero.o meu_racional.o
	./prog

main.o: numero.o meu_racional.o
	gcc -c main.c

numero.o: 
	gcc -c numero.c

meu_racional.o:
	gcc -c meu_racional.c

clean:
	rm -rf *.o *~ prog
