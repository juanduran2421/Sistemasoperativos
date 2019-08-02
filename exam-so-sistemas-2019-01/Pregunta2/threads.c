#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include "common.h"
#include "common_threads.h"
#include "mycommon.h"
 
puerta miPuerta; 
 
double v = 0;

void *worker(void *arg) {
    sleep(2);
    double z = 25;
    double y = 350;

    v =  (z / y);
    return NULL;
}

void *worker1 (void *arg){
	double x = 1250;
	v = x * v;
	return NULL;
	
	
}

int main(int argc, char *argv[]) {
   
    pthread_t p1, p2;
    crear_puerta(miPuerta);
    Pthread_create(&p1, NULL, worker, NULL); 
    Pthread_create(&p2, NULL, worker1, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value   : %f\n", v);
    return 0;
}
