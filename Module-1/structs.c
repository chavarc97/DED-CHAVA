#include <stdio.h>
/*==============================
      REPASO DE ESTRUCTURAS 
=================================*/

/* 
   typedef : nos permite definir un tipo de dato nuevo, basado
   en uno existente.
   Sintaxis:
    a)  
        typedef struct nombre_struct
        {
          variables
        } nombre_struct;
    b)
        struct nombre_struct
        {
          variables
        }
        //typedef tipo nuevo_nombre
        typedef struct nombre_struct nombre_struct

    Despues de utilizar este typedef, tanto a) o b) ya podremos
    crear estructuras nuevas tipo estructura de la siguiente manera:

        nombre_struct mi_estruct1;   // estructura 
        nombre_struct * ptr_e;       // apuntador a estructura

    https://www.educative.io/answers/how-to-use-the-typedef-struct-in-c
    
*/

/* Creamos la estructura nodo: de ahora en delante "node" es un nuevo tipo de dato tipo estructura  podemos utlizarlo de la siguiente forma:
  node nodo1;       <- un nuevo nodo llamado nodo1.
  node *ptr_nodo;   <- un apuntador a un tipo de dato nodo.
  */
typedef struct node
{
  int n;    // int number
  float f;  // a float
  char *s;  // a char
  int i;
  char c2;
  char name[100];
}node;

/* quiz , cual es el tamanio de esta estructura?
          cual es el tamanio de un apuntador a esta estructura?
*/ 

int structs()
{
  printf(" = = = = = = = = = = = = = = = = = = = \n");
  node n;
  n.n = 5;
  n.f = 2.999;
  n.s = "s";
  

  node *ptr_n = &n;
  printf("sizeof struct :%ld , sizeof ptr %ld\n",
          sizeof(node), sizeof(ptr_n));

  /* Recuerda que para acceder a los miembros de una estructura,
  se utiliza el operador "." (punto) */
  printf("node : %d, %f y %s \n", 
          n.n, n.f, n.s);

  /* La principal diferencia con un apuntador a una estructura es 
   que utilizaremos el operador "->" (flecha) para acceder a sus atributos */
  
  printf("node : %d, %f y %s \n", 
          ptr_n->n, ptr_n->f, ptr_n->s);
  
  return 0;
 
}

int main()
{
  structs();
}

/* Ejercicio:
  Declara una estructura "vehicle" con los atributos "brand" y "model"
  Utiliza typedef para ahorrar lineas en la declaracion.
  ej.  "Honda", 2001

  En el main, crea (instancia) 4 Vehiculos.

  Crea una funcion "vehicle_set" que reciba la direccion de un vehiculo y haga
  set a sus valores (Marca y modelo) con datos pasados a la funcion. 
  Inicializa asi 3 de tus vehiculos.

  ej.  vehicle_set(ptr, "Ford", 2020);
       vehicle_set(another, name1var, year);

 
  Para no olvidar el uso de estructuras, El 4to vehiculo inicializalo de forma
  regular sin utilizar la funcion anterior.

  Crea una funcion que reciba un apuntador a un vehiculo e imprima sus
  caracteristicas */