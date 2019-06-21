# 2019_06_21

El dia de hoy se revisaorn conceptos basicos respeco al estado en el que se puede encontrar unproceso en sistesma operativo: *Waiting* , *Ready* ,*Running* y *Done*

Se revisó el comando `process-run.py` que es un aplicativo provisto por el autor
 del texto guía del libro.                                                      
                                                                                
* `process-run.py` aplicativo que simula la ejecución de procesos y sus operacio
nes o en CPU o de I/O                                                           
                                                                                
* `README-process-run` documento que describe la utilización del comando `proces
s-run.py`. 

---

Ejecucion de ejemplo:
``` 
./process-run.py -l 3:0,3:100 -L 3 -c -p                                        
```                                                                             
Esta ejecucion lo que permite es simular la ejecucion de dos procesos.Un primer proceso intensivo en I/O (`3:0`) y un segundo proceso intensivo en CPU (`3:100`).


