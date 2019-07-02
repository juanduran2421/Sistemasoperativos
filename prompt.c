#define _POSIX_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "practica1.h"








void mostrar_prompt() {

  int i,ultima_barra,aux2,fallo;
  char aux;
  char *aux3;
  char *login;
  char nombre_host[256];
  char dir_actual[1000];
  char carpeta_actual[1000];
 
  fallo=0; /* inicializamos fallo.Esta variable nos dira si tuvimos algun fallo */
  /* en alguna llamada de la que dependa el prompt.Si fallo es verdadero */
  /* mostraremos un prompt mas sencillo que solo muestre "$" */

 
  login=getenv("USER");/* cogemos el login del usuario */
  if (login==NULL){
                   printf("microsh: No se pudo obtener el login del usuario\n");
                   fallo=1;
  } 

  aux2=gethostname(nombre_host,256); /* cogemos el nombre del host actual */
  if (aux2==-1){
                perror("microsh: No se pudo obtener el host del usuario");
                fallo=1;
  }

  aux3=getcwd(dir_actual,1000);
/* cogemos el nombre del directorio de trabajo actual */
  if (aux3==NULL){
                 perror("microsh: No se pudo obtener el directorio actual");
                 fallo=1;
  }



  if (!fallo) { /* las llamadas funcionaron todas correctamente */ 




  /* pero ahora solo nos interesa saber el nombre de la carpeta en la que */
  /* estamos metidos para mostrarla en el prompt, no toda la direccion */

  i=0;

  while((aux=dir_actual[i])!=0){
      
    if (aux=='/') ultima_barra=i;
    i++;
  }
 
 
  if (ultima_barra==0) strcpy(carpeta_actual,dir_actual);
            /* esta ultima barra es la del directorio raiz y nos interesa verla */
   else strcpy(carpeta_actual,&dir_actual[ultima_barra+1]); 
	    /* copiamos solo el nombre de la carpeta */ 

/* y ahora mostramos el prompt por pantalla */
	      
  printf("[%s@%s %s]$ ",login,nombre_host,carpeta_actual);

  fflush(stdout); /* para cuando metamos un script como entrada standard de */
                  /* microsh.Asi nos saldran los prompts en el orden adecuado, */
		  /*sino salen al final */


  } /* del if de la linea if(!fallo) */


  else {  /* ha habido algun fallo en alguna llamada del prompt */

        printf("$");
        fflush(stdout); 

  } /* del ultimo else */


} /* de mostrar_prompt */

