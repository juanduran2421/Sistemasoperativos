#define _POSIX_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "practica1.h"






void main(int argc,char *argv[]) {
 
#define MAX_PUNT 1000
#define MAX_COMANDO 1000

int hubo_cd;  /* booleano que dice si ejecutamos un comando tipo cd */
int valido;   /* booleano que dice si el comando es valido sintacticamente */
int ultnulo;  /* posicion del ultimo null en punt */  
char *comando;/* cadena del comando que tomamos de pantalla */
char *punt[MAX_PUNT]; /* vector de punteros que apuntan a la matriz con la */
                      /*  informacion del comando.Tiene longitud MAX_PUNT */
char aux[MAX_COMANDO]; /* cadena del comando en el caso de que microsh se */
                       /* ejecute con argumento */ 



senyalizar(1); /* ignoramos SIGQUIT y SIGINT poniendo un 1*/


while (1) {
  
        
 

  if (argc==1) mostrar_prompt();  /* mostramos el prompt */
  


  if(argc>1){ /* leemos comando,caso remoto */
     
    
    capturar_sigterm(); /* capturamos la senyal SIGTERM */

  
    if(strlen(argv[1])>MAX_COMANDO){
      printf("microsh: Comando demasiado largo\n");
      exit(-1);
    }

    if(argc>2){
     printf("microsh: Solo se permite un comando\n");
     exit(-1);
    }

    strcpy(aux,argv[1]);
    aux[(strlen(argv[1]))]='\n'; /* para que lo acepte nuestro automata */
    comando=aux;
           
  }/* del if */
   
  else comando=leer_comando(); /* leemos el comando */  
                               /* caso iterativo */



  valido=comprobar_comando_correcto(comando,punt,&ultnulo);
       /* comprobamos si el comando es correcto sintacticamente */ 

  if(!valido) printf("microsh: Error sintactico\n");

  else {

  hubo_cd=exit_y_cd(punt);
        /* salimos de microsh si hacemos exit o cambiamos el directorio actual de */
        /* trabajo si hacemos cd , y decimos a microsh si hicimos cd para */
        /* que no intente ejecutar con la funcion ejecutar "mediante hubo_cd" */

  if (!hubo_cd) ejecutar(punt,ultnulo);


 
   } /* del else */

  

  if(argc>1){
                 enterrar_zombies(s_plano2,pid_ult,1);
                 /* esperamos si queda algun proceso antes de morir */              
                 exit(terminacion);
                /* para salir del while */
                /* hacemos que microsh acabe y devuelva como acabo su comando, en */
                /* su estado de terminacion */
  }

    
  }  /* del while */


} /* del main */





