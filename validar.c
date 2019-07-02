#define _POSIX_SOURCE
#include <ctype.h>
#include <stdio.h>
#include "practica1.h"





int comprobar_comando_correcto(char *l,char * ptr[1000],int *ultnul) {




 int es_caracter(char car) {
  if (isalnum(car)||car=='_'||car=='/'||car=='-'||car=='+'||car=='%'||car=='.'
      ||car==':') return 1; 
                   else return 0;
 }

  


#define MAX_PTR 1000   /* numero de filas con info sobre el comando */
                       /* coincide con la longitud de ptr */
#define COL   100      /* numero de columnas con info sobre el comando */
#define ok 50          /* si estado vale ok,se da valida la linea del comando */
#define error 60   /* si estado vale error,no se da valida la linea del comando */  

  int i =0; /* variable para recorrer el comando, que en esta funcion es l */
  int k;    /* variable de apoyo para hacer bucles */
  int nulo; /* variable que dice la posicion del ultimo NULL en ptr */  
  int estado =0; /* variable que dice en que estado del automata estamos */
  int f=0;  /* variable para acceder a las filas de cadenas */
  int c=0;  /* variable para acceder a las columnas de cadenas */

  static char cadenas[MAX_PTR][COL]; 

  /* matriz que guarda la informacion de */
  /* nuestro comando,con dimensiones MAX_PTR x COL, que significan : */
  /* numero filas = longitud de PTR y numero columnas =  longitud informacion */
  /* la definimos estatica para no perder su informacion ya que  pasamos por */ 
  /* referencia el vector ptr que apunta a dicha matriz */
                      

  /* apunto ptr a cadenas */

  ptr[0]=NULL; nulo=0; /* suponemos inicialmente el comando vacio */
for (k=1;k<=(MAX_PTR)-1;k++) ptr[k]=&cadenas[k][0];

/* recorro el automata para guardar la linea y ver si es valida */

while ( estado != ok && estado != error ) {


    switch (estado) {
      
    case 0: /* estado inicial */
           if (l[i]=='\n') estado=ok;
            else if (l[i]==' ') estado=1;
             else if (es_caracter(l[i])){
                                         estado=2;
					 /* ya no es el comando vacio */
                                         /* y apuntamos ptr[0] donde le toca */ 
                                         ptr[0]=&cadenas[0][0];
                                         cadenas[f][c]=l[i];
                                         c++;
	     }
              else estado=error;
           break;  


    case 1: /* blancos iniciales */
           if (l[i]=='\n') estado=ok;
            else if (l[i]==' ') estado=1;
	     else if (es_caracter(l[i])){
                                         estado=2;
                                         /* ya no es el comando vacio */
                                         /* y apuntamos ptr[0] donde le toca */
                                         ptr[0]=&cadenas[0][0];
                                         cadenas[f][c]=l[i];
                                         c++;
	     }
              else estado=error;
           break;
      

    case 2: /* tokens de comando y argumentos */
           if (l[i]=='\n'){
                           estado=ok;
                           cadenas[f][c]=0;
                           nulo=f+1; ptr[nulo]=NULL;
                           /* inicializamos la informacion de las redirecciones */
                           /* y de los tipos de separadores */
                           for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
                           
	   }
	    else if (es_caracter(l[i])){
                                        estado=2;
                                        cadenas[f][c]=l[i];   
                                        c++;
	    }
	     else if (l[i]==' '){
                                 estado=3;
                                 cadenas[f][c]=0;
                                 f++; c=0;
	     }
              else if (l[i]=='<'){
                                  estado=4;
                                  cadenas[f][c]=0;
                                  nulo=f+1; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
                                  for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
                                  /* informamos que hay redireccion entrada */ 
                                  cadenas[nulo+1][0]=1;
                                  f=f+3; c=0; 
	      }
	       else if (l[i]=='>'){ 
                                   estado=8;
                                   cadenas[f][c]=0;
                                   nulo=f+1; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
                                   for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				   /* informamos que hay redireccion salida */
                                   cadenas[nulo+1][1]=1;
                                   f=f+4; c=0; 
	       }
                else if (l[i]==';'){
                                    estado=12;
				    cadenas[f][c]=0;
				    nulo=f+1; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
				    for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
                                    /* informamos que hay separador ; */
				    cadenas[nulo+1][2]=1;
				    f=f+5; c=0;
		}
                 else if (l[i]=='|'){
                                    estado=14;
				    cadenas[f][c]=0;
				    nulo=f+1; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
				    for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
                                    /* informamos que hay separador || */ 
				    cadenas[nulo+1][3]=1;
				    f=f+5; c=0;
		}
                  else if (l[i]=='&'){
                                    estado=17;
				    cadenas[f][c]=0;
				    nulo=f+1; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
				    for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				    f=f+5; c=0;
		}
                   else estado=error;
           break;


    case 3: /* blancos entre tokens de argumentos */
           if (l[i]=='\n'){
                           estado=ok;
                           nulo=f; ptr[nulo]=NULL;
                           /* inicializamos la informacion de las redirecciones */
                           /* y de los tipos de separadores */
                           for (k=0;k<=5;k++) cadenas[nulo][k]=0;
	   }
            else if (es_caracter(l[i])){
                                        estado=2;
                                        cadenas[f][c]=l[i];
                                        c++;
	    }
             else if (l[i]==' ') estado=3;
              else if (l[i]=='<'){
                                  estado=4;
                                  cadenas[f][c]=0;
                                  nulo=f; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
                                  for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				  /* informamos que hay redireccion entrada */
                                  cadenas[nulo+1][0]=1;
                                  f=f+2; c=0;
	      }
               else if (l[i]=='>'){
                                  estado=8;
                                  cadenas[f][c]=0;
                                  nulo=f; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
                                 for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				/* informamos que hay redireccion salida*/
                                  cadenas[nulo+1][1]=1;
                                  f=f+3; c=0;
	       }
                else if (l[i]==';'){
                                    estado=12;
				    nulo=f; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
				for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				/* informamos que hay separador ; */
				    cadenas[nulo+1][2]=1;
				    f=f+4; c=0;
		}
                 else if (l[i]=='|'){
                                    estado=14;
				    cadenas[f][c]=0;
				    nulo=f; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
				for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				/* informamos que hay separador || */
				    cadenas[nulo+1][3]=1;
				    f=f+4; c=0;
		}
                  else if (l[i]=='&'){
                                    estado=17;
			       	    nulo=f; ptr[nulo]=NULL;
                             /* inicializamos la informacion de las redirecciones */
                             /* y de los tipos de separadores */
		       	            for (k=0;k<=5;k++) cadenas[nulo+1][k]=0;
				    f=f+4; c=0;
		}         
                   else estado=error;
           break;


    case 4: /* hay redireccion de entrada */
           if (l[i]==' ') estado=5;
            else if (es_caracter(l[i])){
                                        estado=6;
                                        cadenas[f][c]=l[i];
                                        c++;
	     }  
             else estado=error;
           break;


    case 5: /* blancos antes de token de redireccion de entrada */
           if (l[i]==' ')estado=5;
            else if (es_caracter(l[i])){ 
                                        estado=6;
                                        cadenas[f][c]=l[i];
                                        c++;
	    }                           
             else estado=error;
           break;


    case 6: /* token redireccion de entrada */
           if (l[i]=='\n'){
                           estado=ok;
                           cadenas[f][c]=0;
	   }
	    else if (es_caracter(l[i])){
                                        estado=6;
                                        cadenas[f][c]=l[i];
                                        c++;
	    }					
             else if (l[i]==' '){
                                 estado=7;
                                 cadenas[f][c]=0;
                                 f++; c=0;
	     }
              else if (l[i]=='>'){
                                  estado=8;
                                  cadenas[f][c]=0;
				  /* informamos que hay redirecion salida */
                                  cadenas[nulo+1][1]=1;
                                  f++; c=0;
	      }
                                          
               else if (l[i]==';'){
                                   estado=12;
				   cadenas[f][c]=0;
				   /* informamos que hay separador tipo ; */
				   cadenas[nulo+1][2]=1;
				   f=f+2; c=0;
		}
                else if (l[i]=='|'){
                                    estado=14;
				    cadenas[f][c]=0;
                                    /* informamos que hay separador tipo || */
				    cadenas[nulo+1][3]=1;
				    f=f+2; c=0;
		}
                 else if (l[i]=='&'){
                                    estado=17;
			       	    cadenas[f][c]=0;
				    f=f+2; c=0;
		}                
                  else estado=error;
           break;


    case 7: /* blancos despues de token de redireccion de entrada */
           if (l[i]=='\n'){
                           estado=ok;
                           cadenas[f][c]=0;
	   }
            else if (l[i]==' ') estado=7;
             else if (l[i]=='>'){
                                 estado=8;
                                 /* informamos que hay redireccion salida */
                                 cadenas[nulo+1][1]=1;
	     }
              else if (l[i]==';'){
                                  estado=12;
                                  /* informamos que hay separador tipo ; */
			          cadenas[nulo+1][2]=1;
			          f=f+1; c=0;
		}
               else if (l[i]=='|'){
                                    estado=14;
                                    /* informamos que hay separador tipo || */
				    cadenas[nulo+1][3]=1;
				    f=f+1; c=0;
		}
                else if (l[i]=='&'){
                                    estado=17;
				    f=f+1; c=0;
		}                 
                 else estado=error;
           break;


    case 8: /* hay redireccion de salida */
           if (l[i]==' ') estado=9;
            else if (es_caracter(l[i])){
                                        estado=10;
                                        cadenas[f][c]=l[i];
                                        c++;
	    }
             else estado=error;
           break;


    case 9: /* blancos antes de token de redireccion de salida */
           if (l[i]==' ') estado=9;
            else if (es_caracter(l[i])){
                                        estado=10;
                                        cadenas[f][c]=l[i];
                                        c++;
	    }
             else estado=error;
           break;

              
    case 10: /* token de redireccion de salida */
            if (l[i]=='\n'){
                            estado=ok;
                            cadenas[f][c]=0;
	    }
             else if (es_caracter(l[i])){
                                         estado=10;
                                         cadenas[f][c]=l[i];
                                         c++;
	     }
              else if (l[i]==' '){
                                  estado=11;
                                  cadenas[f][c]=0;
	      }
               else if (l[i]==';'){
                                  estado=12;
                                  /* informamos que hay separador tipo ; */
			          cadenas[nulo+1][2]=1;
			          f=f+1; c=0;
		}
                else if (l[i]=='|'){
                                    estado=14;
                                    /* informamos que hay separador tipo |1 */
				    cadenas[nulo+1][3]=1;
				    f=f+1; c=0;
		}
                 else if (l[i]=='&'){
                                    estado=17;
				    f=f+1; c=0;
		} 
                  else estado=error;
            break;


    case 11: /* blancos despues de token de redireccion de salida */
            if (l[i]=='\n'){
                            estado=ok;
	    }
             else if (l[i]==' ') estado=11;
              else if (l[i]==';'){
                                  estado=12;
                                  /* informamos que hay separador tipo ; */  
			          cadenas[nulo+1][2]=1;
			          f=f+1; c=0;
		}
               else if (l[i]=='|'){
                                    estado=14;
                                    /* informamos que hay separador tipo || */
				    cadenas[nulo+1][3]=1;
				    f=f+1; c=0;
		}
                else if (l[i]=='&'){
                                    estado=17;
				    f=f+1; c=0;
		} 
	         else estado=error;
            break;


    case 12: /* hay separador tipo ";" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=13;
              else estado=error;
            break;


    case 13: /* blancos despues de separador tipo ";" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=13;
              else estado=error;
            break;


    case 14: /* hay indicios de tener un separador tipo "||" */
            if (l[i]=='|') estado=15;
	     else estado=error;
            break;


    case 15: /* hay separador tipo "||" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=16;
	     else estado=error;
            break;


    case 16: /* blancos despues de separador tipo "||" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=16;
	      else estado=error;       
            break;


    case 17: /* habra separador tipo "&" o tipo "&&" o segundo plano */
            if (l[i]=='\n'){
	                    estado=ok;
			    /* informamos que hay segundo plano */
			    cadenas[nulo+1][5]=1;
	    }
             else if (es_caracter(l[i])){
	                                 estado=2;
                                         /* informamos que hay separador tipo & */
				         cadenas[nulo+1][5]=1;
				         cadenas[f][c]=l[i];
				         c++;
	     }
              else if (l[i]=='&'){
                                  estado=18;
                                  /* informamos que hay separador tipo && */
				  cadenas[nulo+1][4]=1;
	      }
               else if (l[i]==' ') estado=20;
	        else estado=error;
            break;


    case 18: /* hay separador tipo "&&" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=19;
              else estado=error;
            break;


    case 19: /* blancos despues de separador tipo "&&" */
            if (es_caracter(l[i])){
                                   estado=2;
				   cadenas[f][c]=l[i];
				   c++;
	    }
             else if (l[i]==' ') estado=19;
              else estado=error;
            break;


    case 20: /* blancos despues de separador tipo "&" */
            if (l[i]=='\n'){
	                    estado=ok;
			    cadenas[nulo+1][5]=1;
	    }
             else if (es_caracter(l[i])){
	                                 estado=2;
				         cadenas[nulo+1][5]=1;
				         cadenas[f][c]=l[i];
				         c++;
	     }
	      else if (l[i]==' ') estado=20; 
               else estado=error;
            break;



      } /* del switch */

/* comprobamos que los tokens no sean mas grande de lo estipulado ni que haya mas 
   tokens de los tambien estipulados */

    if (f>=MAX_PTR || c>=COL) {
      printf("microsh: Demasiados tokens o token demasiado grande\n ");
      return 0;  /* no se acepta el comando */
    }



i++;


   }  /*  del while  */

     /* ultnul es la posicion del ultimo nulo  de ptr */

*ultnul=nulo;




 if (estado==ok) return 1; /* se acepta el comando */ 
 else return 0 ; /* no se acepta el comando */
 
      
} /* de la funcion comprobar_comando_correcto */
