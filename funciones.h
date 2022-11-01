#ifndef FUNCIONES_H //Ejecuta este archivo antes de comprimir.
#define FUNCIONES_H//Define el la cabecera que será importada por otros archivos.

//Las variable declaradas sin extern solo se usan en funciones.c.

char *user;  //Declaramos un puntero a caracteres llamado user, donde se guardará el valor de getlogin() que devuelve el usuario actual y se encuentra en el paquete unistd.h.
char cwd[1024], hostname[128]; //Declaro en primer lugar msg que es un vector de caracteres donde se va a guardar la entrada del ususario en nuestro terminal, el segundo cwd 						     guardará la ruta de datos actual y hostname va a guardar el nombre del administrdor del equipo.
extern void salida(); //Declaramos la función salida que no va delvolver ningún valor, sino que va a imprimir la estructura de nuestra línea en comandos. La declaramos con extern para que cualquier 				archivo que incluya la cabecera pueda usarla.
extern char* minuscula(char *s1);//Declaramos la función misucula en la cabecera, para que cualquier archivo que la incluya pueda usarla. Esta recibe como parámetro un puntero a caracteres y devuelve 				un resultado del mismo tipo.  La declaramos con extern para que cualquier archivo que incluya la cabecera pueda usarla.
int j, len; //Declaramos dos enteros, j para las iteraciones del bucle, y len para guardar la longitud de una string haciendo uso de la función strlen.

#endif //Finalizar si la ejecución se ha realizado correctamente.
