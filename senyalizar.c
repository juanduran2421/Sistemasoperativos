#define _POSIX_SOURCE
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "practica1.h"



void senyalizar(int ignorar) {

  struct sigaction act;
  
  if (ignorar) act.sa_handler = SIG_IGN;
   else act.sa_handler = SIG_DFL;
  sigaction(SIGQUIT,&act,NULL);
  sigaction(SIGINT,&act,NULL);
  
} 





void on_sigterm(int signumber){

  int statloc;


  while(1) waitpid(-1,&statloc,WNOHANG);
  /* Esperaremos a que nos llegue SIGKILL */
  /* Este manejador solo se ejecutara cuando microsh sea ejecutado */
  /* desde el servidor remoto de la practica 2.Y el bucle infito es  */
  /* porque el servidor mandara sigterm a todos los procesos de su grupo */
  /* para que terminen,y  mientras microsh se entretendra haciendoles */
  /* waitpids, que ahorraremos de hacerlos despues al servidor */

}


void capturar_sigterm(){

  struct sigaction act;

  act.sa_handler=on_sigterm;
  sigaction(SIGTERM,&act,NULL);

}














