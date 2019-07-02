/****************************************************/

/* Programa creado por Rubén Esteve Carrillo */

/* ruescar@inf.upv.es */

/****************************************************/

/* variable que utilizaremos para devolver a "microrshd" la */
/*terminacion de nuestro comando */

int terminacion; 


int pid_ult; /* pid del ultimo mandato del comando */


/* variable modificada desde la funcion "ejecutar",que su ultimo */
/* valor dice si el ultimo mandato del comando remoto esta en segundo plano. */
/* y de este modo esperaremos a pid_ult para devolver su estado de terminacion */
/* a "microrshd" */

int s_plano2; 




/* Ignora las senyales SIGINT y SIGQUIT */
/* Se encuentra en senyalizar.c */

void senyalizar(int );


/* Captura la senyal SIGTERM en el programa microsh */
/* Se encuentra en senyalizar.c */

void capturar_sigterm();


/* Se encarga de recoger el estado de los hijos de microsh y liberar */ 
/* sus recursos */
/* Se encuentra en zombies.c */

void enterrar_zombies(int ,int,int );


/* Muestra el prompt de microsh */
/* Se encuentra en prompt.c */

void mostrar_prompt();


/* Lee el comando de microsh por la entrada estandard */
/* Se encuentra en leer_comando.c */

char * leer_comando();


/* Comprueba que la sintaxis del comando sea correcta (Automata) */
/* Se encuentra en validar.c */

int comprobar_comando_correcto(char *,char * ptr[1000],int *);


/* Funcion especial para manipular los comandos "exit" y "cd" */
/* Se encuentra en exit_y_cd.c */

int exit_y_cd(char *punt3[1000]);


/* Ejecuta el comando que recibe microsh */
/* Se encuentra en ejecutar.c */

int ejecutar( char * punt2[100],int );


/* Redirigen la entrada estandard,la salida estandar,y la salida de errores */
/* al archivo especificado */
/* Se encuentra en redirecciones.c */

void red_ent(char *);
void red_sal(char *);
void red_err(char *);
