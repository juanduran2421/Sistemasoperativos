all: microsh

microsh: microsh.o senyalizar.o zombies.o prompt.o leer_comando.o validar.o exit_y_cd.o ejecutar.o redirecciones.o
	gcc -o microsh  microsh.o ejecutar.o validar.o prompt.o exit_y_cd.o zombies.o leer_comando.o senyalizar.o redirecciones.o  

microsh.o: microsh.c practica1.h
	gcc -c microsh.c 

senyalizar.o: senyalizar.c practica1.h
	gcc -c senyalizar.c 

zombies.o: zombies.c practica1.h
	gcc -c zombies.c 

prompt.o: prompt.c practica1.h
	gcc -c prompt.c 

leer_comando.o: leer_comando.c practica1.h
	gcc -c leer_comando.c 

validar.o: validar.c practica1.h
	gcc -c validar.c 

exit_y_cd.o: exit_y_cd.c practica1.h
	gcc -c exit_y_cd.c 

ejecutar.o: ejecutar.c practica1.h
	gcc -c ejecutar.c 

redirecciones.o: redirecciones.c practica1.h
	gcc -c redirecciones.c 





