#include <unistd.h> //Incluye la librería unistd.h de donde usaremos la funcion chdir() para cambiar de directorio, así como la operación getpid que nos devuelve la etiqueta del proceso hijo, además  			nos da los nombres de usuario, administrador y la ruta de directorios que usaremos en este archivo.
#include <string.h> //Incluye la librería string.h que nos proporciona las funciones strtok para separar por espacios una string, fgets() para poder leer una string por teclado y strcmp() para    			     comparar una string con otra.
#include <ctype.h> //Incluye la librería ctype.h que cotiene la función tolower() que será usada en funciones.c, archivo que a su vez será importado con la cabecera funciones.h.
#include <stdio.h> //Incluye la librería stdio.h que proporciona algunas funciones básicas.
#include "funciones.h" //Incluye la cabecera funciones.h que proporciona dos funciones simples, char* minuscula(char *s1) y void salida(), que se han implementado en el archivo fuente funciones.c.



char* minuscula(char *s1){//Defino la función minuscula que devuelve un puntero a caracteres y recibe como parámetro un puntero de caracteres(*s1). Va a devolver la string apuntada por el 	      				     puntero pero convertida a letras minúsculas.
	len = strlen(s1); //Declara entero llamado len que almacenará el valor devuelto por la función strlen() sobre el puntero pasado como parámetro, siendo este valor la longitud de la string 					en s1.
	for(j = 0; j < len; j++){ //Bucle que comienza en j = 0, e y sigue iterándose mientras sea menor que len, con cada iteración j se incrementa en 1.
		*s1 = tolower(*s1); //Cada elemento apuntado por j va a convertirse en minúscula haciendo uso de la función tolower() de ctype.h.
		s1++; //Apuntamos al siguiente elemento de la string.
	}
	s1 -= len; //Al finalizar, debemos retroceder al primer elemento al que apuntaba el puntero.
	return s1; //Devolvemos el puntero una vez convertido todos sus elementos a minuscula.
}

void salida(){ //Define la función salida de tipo void. No recibe ningún argumento y debe mostrar la línea de comandos.
	 	
	user = getlogin(); //Declaramos un puntero a caracteres llamado user, donde se guardará el valor de getlogin() que devuelve el usuario actual y se encuentra en el paquete unistd.h. 	
	getcwd(cwd, sizeof(cwd)); //Usamos la función getcwd(unistd.h), que recibe como parámetros un puntero a caracteres y el tamaño de ese puntero. En este caso, guardaremos en cwd 					    la ruta de directorio actual.
	gethostname(hostname, sizeof(hostname)); //Usamos la función gethostname(unistd.h), que recibe como parámetros un puntero a caracteres y el tamaño de ese puntero. En este caso 							    guaradaremos en ese puntero el valor del usuario administrador. 
	printf("%s@%s:~%s$ ", user, hostname, cwd); //Mostramos en pantalla la estructura de entrada del shell, esto es "usuario@administrdor:~ruta$ ", tras este mensaje el usuario debe introducir el 							comando a ejecutar.
}

