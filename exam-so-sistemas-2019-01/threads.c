#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"
#include "mycommon.h"

volatile int counter = 0;
puerta miPuerta; 
int loops;
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
    if (argc != 2) { 
	fprintf(stderr, "usage: threads <loops>\n"); 
	exit(1); 
    } 
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    crear_puerta(miPuerta);
    printf("Initial value : %d\n", counter);
    Pthread_create(&p1, NULL, worker, NULL); 
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value   : %d\n", v);
    return 0;
}
