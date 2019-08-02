# Parcial 1
## Pregunta 1
Link usado:
http://diagramas-de-flujo.blogspot.com/2013/01/medir-tiempo-ejecucion-funcion-en-c.html

Para hacer este punto creé dos worker, uno para cada punto pedido, y luego con el codigo del link tome el tiempo que le tomaba a cada worker realizar la tarea.
Yo creo que la diferencia de tiempos podría ser porque un worker solo cierra y abre la puerta una vez, mientras que el otro tiene que hacerlo muchas veces ya que estos comandos estan dentro del fork

### Tiempo transcurrido1 es del primero hilo y Tiempo transcurrido2 es del segundo hilo

 Tiempo transcurrido1: 1.000000
 Tiempo transcurrido2: 1.000000

Tiempo transcurrido1: 1.000000
 Tiempo transcurrido2: 0.000000
 
 Tiempo transcurrido: 1.000000
 Tiempo transcurrido: 2.000000
 
  Tiempo transcurrido1: 2.000000
 Tiempo transcurrido2: 2.000000


Tiempo transcurrido1: 2.000000
 Tiempo transcurrido2: 0.000000



## Pregunta 2

Link usado:http://decsai.ugr.es/~jfv/ed1/c/cdrom/cap3/f_cap34.htm

Para realizar este punto lo que hice fue crear dos worker los cuales en su interior van a tener las variables que son necesarias para sus operaciónes y luego creé una variable global llamada "v" la cual iba a guardar el resultado de dividir "z" con "y", para que después sea multiplicado con "x".

Para todo esto utilicé dos hilos donde cada hilo iba ejecutar uno de los worker.

## Pregunta 3
