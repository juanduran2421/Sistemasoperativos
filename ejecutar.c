#define _POSIX_SOURCE
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include "practica1.h"










int ejecutar( char * punt2[100],int ultnul2){






 
  int ejec(char *file,char *argv[],char *ent,char *sal,int s_plano){
    
    pid_t pid=fork();
    int statloc;

    
    switch(pid) {

    case 0:         /* proceso hijo */

               
                   /* si el hijo no se ejecuta en segundo plano, designoramos */
		   /* las senales SIGQUIT y SIGINT */
    
           if (!s_plano) senyalizar(0); /* el 0 es no ignorar */


                   /* miramos si hay redireccion de la entrada */              

           if(s_plano){  /* distinguimos caso en segundo plano */
                       if (ent!=NULL) red_ent(ent);
	                else red_ent("/dev/null");
	   }
             else   if (ent!=NULL) red_ent(ent);


	   /* miramos si hay redireccion de la salida */
            if(sal!=NULL) red_sal(sal);       
 
                 
           execvp(file,argv);
            /* Si se ejecuta lo siguiente es que "exec" fallo. */
           perror("microsh: Fallo en exec");
           exit(-1);
    
    case -1:
            perror("microsh: Fallo en fork");
            return 0; /* acabo mal ejec */

    default:             /* proceso padre*/

      pid_ult=pid; /* de momento este es el ultimo pid */
      /* esto lo hacemos para devolver el estado de terminacion,cuando el ultimo */
      /* mandato del comando sea en segundo plano.Asi si algun mandato intermedio */
      /* tambien estaba en segundo plano, cuando enterremos los zombies */
      /* cogeremos el valor  de terminacion del ultimo mandato del comando y no */
      /* del que acabe ultimo*/

            if (!s_plano){
	           waitpid(pid,&statloc,0); /* modo sincrono */  
                   if(WIFEXITED(statloc)){ /* el hijo acabo voluntariamente */
		     if(WEXITSTATUS(statloc)){
                                              terminacion=2;
                                              return 0; /* acabo mal ejec */
                                         /* fallo exec o el comando no tuvo exito */
                                              
		                              }
		      else{
                            terminacion=1;
                            return 1;  /* acabo bien ejec */
                                      /* tuvo un hijo,estado terminacion = 0 */
		      }
		   }

              else { /* acabo mal ejec el hijo no acabo voluntariamente */
		         /* por senyal u otro motivo */
                         
	            if(WIFSIGNALED(statloc)){ /* el hijo acabo por senyal */      
                                      printf("microsh: %s acabo por senyal\n",file);
                                      terminacion=3;
                                      return 0; /* acabo mal ejec */ 
 
	      } /* del if anterior */

		   } /* del segundo else */

	    } /* del primer if de default */

    }  /* del switch*/ 
  
  } /* de la funcion ejec */





 int cont,cont_arg,tipo,s_plano;
 char *comando;
 char *argumentos[100];
 char *ent; 
 char *sal;




  cont=0; /* empezamos por la primera instruccion*/

  if (ultnul2==0) return 1; /* comando vacio, no tenemos que hacer nada */
  
  
while (1){

  cont_arg=0;
  tipo=0;/* comando simple,sin separadores*/
  ent=NULL; sal=NULL; /* por si no hay entrada ni salida */
  s_plano=0;/* por si no se ejecuta en segundo plano*/
  comando=punt2[cont];
  argumentos[cont_arg]=punt2[cont];


  /* hacemos el siguiente while para encontrar el primer/siguiente null */
  /* y de paso para hacer un clon de punt2 en argumentos,que queda mas bonito*/
  while(punt2[cont]!= NULL){
             argumentos[cont_arg]=punt2[cont];
             cont++; cont_arg++;
  }
  argumentos[cont_arg]=punt2[cont]; /* metemos el null en argumentos */
 

  /* veamos si hay redirecciones*/

  if (punt2[cont+1][0]==1) ent=punt2[cont+2]; /* metemos la entrada std */
  if (punt2[cont+1][1]==1) sal=punt2[cont+3]; /* metemos la salida std */


  /* veamos si se ejecuta en segundo plano, es decir hay separador */
  /* tipo & segundo plano, & final */

 if ( (punt2[cont+1][5]==1) || (punt2[cont+1][6]==1) ) s_plano=1;

 s_plano2=s_plano; /* s_plano2 es variable global  */

 /* veamos si hay separadores conflictivos en  la primera instrucion del comando */
  /* del tipo "&&" o "||" */

 if (punt2[cont+1][3]==1) tipo=1; /* hay separador tipo || */
   else if (punt2[cont+1][4]==1) tipo=2; /* hay separador tipo && */
              

  /* pasemos a ejecutar el comando */  

 switch (tipo){

 case 0:   /* mandato simple o con separador ";" */
  
        if(!ejec(comando,argumentos,ent,sal,s_plano))
        printf("microsh: Fallo del comando %s \n",comando);
        break;

 case 1:
       if((ejec(comando,argumentos,ent,sal,s_plano))==1) return 1;
       else printf("microsh: Fallo del comando %s \n",comando);

            /* si es correcto el primer mandato para  */
       break;
  
 case 2:     
       if((ejec(comando,argumentos,ent,sal,s_plano))==0){
          printf("microsh: Fallo del comando %s \n",comando);
          return 1;   
       }
            /* si no es correcto el primer mandato para */
       break;

    
  
 } /* del switch */


 

 if (cont==ultnul2){
                    enterrar_zombies(s_plano2,pid_ult,0);
                    /* ponemos valor 0 para suponer que de momento no estamos */
                    /* ejecutando un comando remoto.Luego en el codigo de microsh */
                    /* ya esperaremos si hace falta */
                    return 1; /* hemos acabado el comando correctamente */
          
 }

  else cont+=4; /* pasamos al siguiente mandato del comando */
 


} /* del while */

  
}  /* de la funcion ejecutar */


