# Lenguaje C - 101
En esta clase se hizo una revisión muy rápida de un programa sencillo en C que imprime el mensaje hola mundo. Después se mostró la forma como se genera una librería de enlace estático y como la funcionalidad implementada en esta es invocada desde un programa en C.

Se desarrollaron tres programas:

<li type="disc"> <a href="https://github.com/juanduran2421/Sistemasoperativos/blob/master/2019_05_24/basico.c"> basico.c </a> </li>

<li type="disc"> <a href="https://github.com/juanduran2421/Sistemasoperativos/blob/master/2019_05_24/libfun.c"> libfun.c </a> </li>

<li type="disc"> <a href="https://github.com/juanduran2421/Sistemasoperativos/blob/master/2019_05_24/linfun.h"> libfun.h </a> </li>

Para compilar el programa se llevan a cabo los siguientes pasos:

### 1.Generar la librería

    gcc -c libfun.c -o libfun.o
    ar rcs libfun.a libfun.o
  
### 2.En el paso anterior se generó el archivo libfun.a. Ahora enlazaremos el programa basico.c con la libreria libfun.a

    gcc basico.c -L. -lfun -o basico
  
### 3.Finalmente, el programa se ejecuta:

    ./basico
