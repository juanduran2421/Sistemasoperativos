#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "practica1.h"






  void red_ent(char *entra){

    int fd1;
  
    fd1= open(entra,O_RDONLY,0644);
    if (fd1<0){
      perror("microsh: Fallo red. entrada en open");
      exit(-1);
    }
  
    close(0);
    dup(fd1);
    close(fd1);

  }


  void red_sal(char *salid){

    int fd2,aux;
   
    fd2= open(salid,O_WRONLY |O_CREAT,0644);
    if (fd2<0){
      perror("microsh: Fallo red. salida enn open");
      exit(-1);
    }
   
    close(1);
    aux=dup(fd2);
    if (aux==1) close(fd2);
     else {  /* el descriptor de entrada standard estaba libre */
           dup(fd2);
           close(fd2);
           close(0);
     }   
 
  }


 void red_err(char *err){

    int fd3,aux,parar,i;
    int v[2]; /* vector en el que decimos si estaban abiertas la entrada */
              /* standard y la salida standar, y hay que cerrarlas al final */


    /* inicializamos el vector */
    v[0]=3;
    v[1]=3;


    fd3= open(err,O_WRONLY |O_CREAT,0644);
    if (fd3<0){
      perror("microsh: Fallo red. salida enn open");
      exit(-1);
    }
   
    close(2);
    parar=0;

    i=0;

    while(!parar){

    aux=dup(fd3);

    if (aux==2){
                close(fd3);
                parar=1;
    }
    else v[i]=aux;   

    i++;
 
    }/* del while */



    if (v[0]!=3) close(v[0]);
    if (v[1]!=3) close(v[1]);
    close(fd3);

  }
