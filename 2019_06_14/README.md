# Revision  de las funciones para gestion de procesos en C


*[fork-basico.c](fork-basico.c)

Para llevar a cabo la solución del problema planteado en clase debe descargar los siguientes archivos:

*[solucion.c](solucion.c)

*[solucion.h](solucion.h)

*[mainsol.c](mainsol.c)- este es un ejemplo


Para generar la libreria se ejecutan los siguientes comandos:

    gcc -c solucion.c
    ar rc libsolucion.a solucion.o
  
Para compilar su programa usand la nueva libreria:

    gcc -o mainsol -L. mainsol.c -lsolucion 
