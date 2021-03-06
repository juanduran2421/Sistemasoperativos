#include "common.h"
#include "common_threads.h"
#include "mycommon.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <time.h>


volatile int counter = 0;
puerta miPuerta; 
int loops;

void *worker(void *arg) {
   clock_t start = clock();
	
    int i;
    cerrar_puerta(miPuerta);
    for (i = 0; i < loops; i++) {
    
	counter++;
    }
    abrir_puerta(miPuerta);
     printf("\n Tiempo transcurrido1 : %f", ((double)clock() - start));
    return NULL;
}

void *worker1(void *arg) {
    clock_t start = clock();
    int i;
    
    for (i = 0; i < loops; i++) {
    cerrar_puerta(miPuerta);
	
  counter++;
   abrir_puerta(miPuerta);
    }
    printf("\n Tiempo transcurrido2: %f", ((double)clock() - start));
    return NULL;
}
int main(int argc, char *argv[]) {
    if (argc != 2) { 
	fprintf(stderr, "usage: threads <loops>\n"); 
	exit(1); 
    } 
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    crear_puerta(miPuerta);
    printf("Initial value : %d\n", counter);
    Pthread_create(&p1, NULL, worker, NULL); 
    Pthread_create(&p2, NULL, worker1, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("\n Final value   : %d\n", counter);
    return 0;
}
