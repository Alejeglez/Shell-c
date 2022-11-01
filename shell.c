#include <unistd.h> //Incluye la librería unistd.h de donde usaremos la funcion chdir() para cambiar de directorio, así como la operación getpid que nos devuelve la etiqueta del proceso hijo. 
#include <string.h> //Incluye la librería string.h que nos proporciona las funciones strtok para separar por espacios una string, fgets() para poder leer una string por teclado y strcmp() para    			     comparar una string con otra.
#include <ctype.h> //Incluye la librería ctype.h que cotiene la función tolower() que será usada en funciones.c, archivo que a su vez será importado con la cabecera funciones.h.
#include <stdio.h> //Incluye la librería stdio.h que proporciona algunas funciones básicas.
#include <sys/wait.h> //Incluye la librería sys/wait.h que proporciona las funciones de la familia wait que nos harán falta.
#include <sys/types.h> //Incluye la librería sys/types.h que proporciona la declaración de procesos y permite trabajar con ellos con funciones como fork y exec.
#include "funciones.h" //Incluye la cabecera funciones.h que proporciona dos funciones simples, char* minuscula(char *s1) y void salida(), que se han implementado en el archivo fuente funciones.c.
#include <stdlib.h> //Incluye la librería stdlib.h de la que usaremos la función exit().

//Declaración variables globales.



char exitw[5] = "exit\0"; //Declaramos en exitw la cadena de caracteres "exit\0" de tamaño 5, que servirá para conocer si el usuario quiere detener la ejecución del shell.
char quitw[5] = "quit\0"; //Declaramos en quitw la cadena de caracteres "quit\o" de tamaño 5, que también permitirá conocer si el usuario quiere detener la ejecución del shell.
char cdw[3] = "cd\0"; //Declaramos en cdw la cadena de caracteres "cd\0" de tamaño 3, que será útil para saber si el usuario que realizar la operación cd(cambiar de directorio).



//Declaración función principal: es de tipo void por que no debe retornar un valor y detener su ejecución.-
int main(){
	pid_t child_pid; //Declaramos una etiqueta de proceso que se llame child_pid que representará al proceso hijo que ejecutará las instrucciones.
	int status; //Declaramos el entero status que será un argumento para esperar por la ejecuión del proceso hijo hasta un determinado estado.
	int i = 1; //Declaramos un entero con i con el valor de 1, nos permitirá crear un bucle while que ejecute nuestro shell hasta que se escriba exit o quit.
	char msg[1024]; //Declaramos un vector de caracteres llamado msg que va a ser asignado a la entrada del usuario, con el tamaño máximo de una línea(1024).
	int k = 0; //Declaramos un entero k que nos ayudará a conocer si el usuario ha introducido una instrucción asícrona, ya que se activará a uno en este caso.
	int cont, j; //Declaro un contador(cont) que servirá como índice en el vector de strings tira, j servirá como contador para informarnos en caso de que sea la primera vez que usamos strtok, 		      teniendo que usar minuscula de funciones.h.
	char *ptr, *ejecutable; //Declaramos dos punteros a caracteres, ptr apuntara a la entrada del usuario, y ejecutable será usado para alojar el resultado de la función strtok, 				   que separará la string apuntada por ptr en espacios.
	
	char *tira[128]; //Declaramos en tira un vector de strings(128 de tamaño) que servirá para almacenar los elementos separados por espacios de la entrada del usuario. Se pasará como parámetro 				al exec que ejecutará el proceso hijo.
	
	while(i == 1){ //Mientras i sea 1 este bucle va a seguir ejecutándose.
	
		//Si no estamos en el proceso hijo, debemos ejecutar el proceso padre que contiene el cuerpo de nuestro shell.
			k = 0; //Le damos a k el valor a 0, ya que es una nueva iteración que debe reiniciar esta variable.
			salida(); //Llamamos a la función salida de la cabecera "salida.h", para imprimir la línea de comando de nuestro shell.
			fgets(msg, 1024, stdin); //Leemos el mensaje de que introduce el usuario con fgets de string.h, recibe como parámetros el vector msg, su tamaño y stdin(standard input).
			j = 0; //Ponemos el valor de j a 0, al igual que k porque reiniciamos el valor.
			cont = 0; //Declaro un contador a 0 que servirá como índice en el vector de strings tira.
			ptr = msg; //El puntero ptr apunta al vector pasado como parámetro.
			ejecutable = strtok(ptr, " \t\n\r"); //El puntero ejecutable es igual al valor devuelto por la función strtok(de string.h). Esta recibe como parámetros ptr, que era la entrada 									del usuario y lo que queremos usar como separador, en este caso " \t\n\r" que representa el espacio. En ejecutable se guarda el elemento 									antes del primer espacio poniendo este espacio a '\0'.

			while( ejecutable != NULL) { //Mientras ejecutable sea distinto de NULL, se ejecutará este bucle para separar por espacios la entrada del usuario.
			
				if(j == 0){ //Si j es igual a 0 significa que es la primera iteración y por lo tanto debemos darle un trato especial, ya que antes del primer espacio se escribe el 				     		     comando como cd o ls.
					ejecutable = minuscula(ejecutable);//Lo primero que hacemos es aplicar sobre el puntero ejecutable la función minuscula que definimos en funciones.c. Así 					     				    podemos escribir nuestro comando con o sin minusculas que se ejecutará sin problemas. 
					tira[cont++] = ejecutable;  //Almacenamos el valor del puntero ejecutable en el puntero tira, que avanza de posición tras la iteración. Recordemos que tira es el 			                                            vector que se pasa como parámetro en el execvp y contiene toda la línea que introduce el usuario, con su elemento separados.
					ejecutable = strtok(NULL, " \t\n\r");  //Realizamos otro strtok para separar con espacios pero en este caso no usaremos ptr, si no NULL que es el elemento en el  							                         que nos hemos quedado.
					j++; //Incrementamos j para saber que no estamos en el comando principal que introdujo el usuario.
				}
				
				else{ //Si j es distinto de 0 nos encontramos en el segundo elemento antes de un espacio al que apunte ejecutable.
					tira[cont++] = ejecutable; //Volvemos a almacenar en el puntero tira el elemento separado con espacio, tras eso, avanzará un elemento. 
					ejecutable = strtok(NULL, " \t\n\r"); //Realizamos otro strtok para separar con espacios pero en este caso no usaremos ptr, si no NULL que es el elemento en el  							                        que nos hemos quedado.
				}

   			}
		   		tira[cont++] = 0; //El último elemento del puntero tira es igual a 0, para permitir la ejecución de instrucciones de un único elemento(ej. ls sin argumentos).
		   		if (strcmp(tira[0], exitw) == 0 || strcmp(tira[0], quitw) == 0){ //En este if usamos la función strcmp del módulo string.h que recibe como parámetros dos 											            strings, siendo tira[0] el primer elemento de la entrada del ususario. Si este es igual a quit o a 													    exit, el valor devuelto por la función es 0, en caso contrario es 1. Si es 0, debemos hacer romper el 												           bucle con break.

		      			return -1;  //Devolvemos -1 para finalizar el programa.
		  		}
		  		else{  //Si no se ha introducido exit o quit.
		  			if(strcmp(tira[0], cdw) == 0){ //Si el valor de tira[0] es cd no se debe lanzar el proceso hijo sino que debemos cambiar el directorio con chdir en el padre.
		  				chdir(tira[1]); //El elemento que contiene el directorio es el segundo en el vector tira(tira[1]) que contiene la instrucción. Por lo que usamos la 									función chdir que permite el cambio de directorio con este elemento como parámetro.
		  			}
		  			else{ //Si no es cd, debemos ejecutar el proceso hijo.
		  				cont -= 2; //Antes de ejecutar el proceso hijo, debemos comprobar que la instrucción introducida no es asíncrona. Para comenzar reducimos la varaible 								   cont en 2, para que tira referencie al último elemento escrito por el usuario({"entrada usuario", "0", '\0'}).
		  				int longitud = strlen(tira[cont]); //Creamos un entero llamado longitud que nos da la longitud de la string a la que apunta tira.
		  				if(tira[cont][longitud-1] == '&'){ //Si este último carácter es igual a '&', el usuario introdujo un comando asíncrono, y debemos darle un trato 												especial. Tenemos que imprimir el pid del hijo por pantalla y seguir ejecutando la terminal sin espera.
		  					tira[cont][longitud-1] = '\0'; //Para que el hijo pueda ejecutar tira, hacemos que el caracter al que hacía referencia ptr2 sea '\0'
		  					k = 1; //Le damos a k el valor 1 para indicarle al hijo que imprima el pid.
		  					child_pid = fork();  //Le asignamos al proceso hijo el valor de fork(), para crearlo.
		  					sleep(0);
		  				}
		  				else{ //Si no es asíncrono lo ejecutamos como normalmente.
		  				child_pid = fork();  //Le asignamos al proceso hijo el valor de fork(), para crearlo.
						waitpid(child_pid, &status, 0); //Esperamos a que el proceso hijo finalicé, esto lo hacemos con waitpid, que recibe como parámetros la etiqueta del hijo, 										 un entero que indica su estado, y 0 porque no usaremos opciones adicionales.
   						}
   		if(child_pid == -1){
			//si -1 ERROR AL CREAR EL HIJO
			printf("Error al crar proceso hijo.");
			return -1;
		}
				
		if(child_pid == 0){ //Si la etiqueta del proceso hijo es 0, significa que ha sido llamado a través de la instrucción fork() y por lo tanto hay que ejecutar las instrucciones. 
			if(k == 1){ //Si k es igual a 1 el usuario ha introducido una operación asíncrona que debe ejecutarse de fondo.
				printf("\n[+]%d\n.", getpid()); //Debemos mostrar el pid del proceso hijo que se obtiene con getpid(), y que sigue la estructura [+]pid. cuando se imprime en el shell 									original.
			}
			execvp(tira[0], tira); //Execvp(de unistd.h) permite ejecutar la instrucción que el usuario pase como parámetro, debiendo antes trabajar un poco con la entrada del      						usuario. Esta función recibe en primer lugar tira[0], el primer elemento de la entrada del usuario, y el vector de strings tira que incluye todos los 							elementos de la entrada del usuario, una vez son separados por espacios.
			exit(0); //Tras la ejecución del comando, finalizamos el hijo.
		   }
    
		
		}
	 }
		    
	}
	return 0;
}
