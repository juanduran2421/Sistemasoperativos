#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "practica1.h"




char * leer_comando(){


#define MAX_COMANDO 1000  
static char comando[MAX_COMANDO];/* cadena del comando que tomamos de pantalla */
                                /* con longitud maxima MAX_COMANDO */
			   /* es estatica para no perderla al terminar leer_linea */
char * aux;


 aux=fgets(comando,MAX_COMANDO,stdin);
 
 if(aux==NULL) {
                printf("exit\n"); /* para que bash continue abajo y quede bonito */
                exit(0);   /* por si se cierra la entrada standard de microsh */
 }
 else return aux;       /* devolvemos el comando leido */


} /* de leer_comando */
