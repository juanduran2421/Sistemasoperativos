#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include "practica1.h"



void enterrar_zombies(int s_plano,int pid_ult,int remoto){


  int statloc,parar;
  pid_t pid;


parar=0;
while(!parar){


  while((pid=waitpid(-1,&statloc,WNOHANG))>0){ /* si devuelve -1 es que no hay */
        /* procesos  en segundo plano y si devuelve 0 es que aun no han acabado */


  if ((s_plano)&&(pid==pid_ult)){ /* estamos en el caso en que el  ultimo mandato */
    /* del comando es en segundo plano.y este es el valor que nos interesa */
    /* devolver a "microrshd" luego */
	             
                   if(WIFEXITED(statloc)){ /* el hijo acabo voluntariamente */

		     if(WEXITSTATUS(statloc)) terminacion=2;
                                         /* fallo exec o el comando no tuvo exito*/
                                              
           
		                              
		     else terminacion=1; /* el comando tuvo exito */
		      
		   }

              else { /* el hijo no acabo voluntariamente */
		         /* por senyal u otro motivo */
                         
	            if(WIFSIGNALED(statloc)) terminacion=3; 
                                             /* el hijo acabo por senyal */      
                                      

		   } /* del segundo else */


	    } /* del if (s_plano) */
               




      } /* del segundo while */

 if(pid==-1) parar=1; /* ya no hay nada mas que mirar */

 if(!remoto) parar=1; /* en el caso de que no estemos en el caso remoto pararemos*/
                      /* y seguiremos ejecutando comandos con microsh */

} /* del primer while */

} /* de enterrar_zombies */
