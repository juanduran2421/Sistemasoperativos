#define _POSIX_SOURCE
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "practica1.h"




int exit_y_cd(char *punt3[1000]){

int aux2;

 
/* primero miramos si ha sido introducido el comando vacio en cuyo caso acabamos */
 
 if (punt3[0]==NULL) return 0;


  /* ahora estudiamos primero si hay un exit */


if(strcmp(punt3[0],"exit")==0){ /* estamos ante un exit en potencia */
                                 /* el cero de detras del exit es porque punt[3] */
				 /*siempre acaba en 0,menoscuando es el comando */
                          /* vacio, para que luego trabaje bien la funcion execvp */

         if (punt3[1]==NULL) exit(0);  /* el comando es "exit" y acabamos microsh */
                          /* han puesto exit y mas cosas, por tanto no es un exit */
                       /* valido y dejamos que de el error al intentar ejecutarse */
                       /*en la funcion ejecutar */

  } /* del primer if */


 else{  /* estudiamos si hay un cd ,para cambiar el directorio de trabajo actual */



  if(strcmp(punt3[0],"cd")==0){ /* estamos ante un cd en potencia */
  
    if (punt3[1]==NULL) ;      /* no hacemos nada,no se especifico el directorio */
     else if (punt3[2]!=NULL) ; /* se ha puesto mas de un argumento a cd y no */
                              /* lo aceptamos y por tanto no hacemos tampoco nada */
           
            else {
                  aux2=chdir(punt3[1]);
                 /* cambiamos el directorio de trabajo especificado */ 
		  if (aux2) perror("microsh: no se pudo cambiar de directorio");
                    
                  return 1; /* decimos que hemos ejecutado un cd y que hay que */
	                     /* volver a leer un nuevo comando */  
                 /* hemos simulado la ejecucion de un comando, en este caso el cd */

	    }/* del ultimo else */

  
  } /* del if de la linea que llama a strcmp con "cd" */


 }/* del primer else */


 return 0; /* si no se ha hecho exit ni cd llegaremos hasta aqui*/


} /* de exit_y_cd */

