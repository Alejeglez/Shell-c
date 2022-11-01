shell: shell.o funciones.o
	gcc -o shell shell.o funciones.o

shell.o: shell.c
	gcc -c shell.c

funciones.o: funciones.c
	gcc -c funciones.c

clean:
	rm *.o shell
