#include <stdio.h>
#include <unistd.h>

/* Apuntadores a funcion :

Un apuntador a funcion es capaz de guardar la direccion donde una funcion se encuentra. Es capaz de ejecutarla y podemos operar este apuntador de la misma manera que ya hemos visto.

La sintaxis para declarar un apuntador a funcion es la siguiente:

tipo_de_retorno (* nombre_de_apuntador) (parametros)

ejemplo:
  int (*ptr)(int, int)

En este caso, "ptr" es un apuntador a cualquier funcion que cumpla con las siguientes caracteristicas:
    - devulve un entero.
    - recibe 2 enteros.
  Al cojunto de caracteristicas le llamaremos "firma de funcion" y nuestro apuntador podra se utilizado para almacenar la direccion de multiples funciones con la misma firma.

Recuerda que tambien puedes usar el typedef para evitar escribir el tipo completo. Lo veras en este ejercicio.

El siguiente ejemplo declara 3 funciones con el misma firma :*/

// suma a y b. retorna el resultado.
int sum(int a, int b)
{
  printf("returning %d+%d\n", a,b);
  return a+b;
}

// resta "b" a "a" y regresa el resultado
int minus(int a, int b)
{
  printf("returning %d-%d\n", a,b);
  return a-b;
}

// mutiplica a x b y regresa el resultado
int mult(int a, int b)
{
  printf("returning %dx%d\n", a,b);
  return a*b;
}

/* Estas 3 funciones, comparten la misma firma y por tanto pueden ser apuntadas por el mismo apuntador que creamos a continuacion: */  
typedef int (*two_operand_func) (int, int);

/* Apartir de este momento "two_operand_func" es un apuntador a 
   funcion de tipo
   Funcion que recibe 2 enteros y retorna un entero" 
   puede ser utilizado de forma 
   convencional como cualquier otro tipo de dato : pasarlo a funciones, 
   guardarlo en arreglos etc. */

/* la funcion func_c a continuacion, recibe un apuntador a funcion, y 3 numeros.
  Ejecutara la funcion pasada por parametro utilizando a y b y al 
  resultado le sumara "c" siendo este el valor final de returno. */

                   //func_ptr este es un function pointer
int func_c(int(*  func_ptr)(int,int), int a, int b, int c)
{
  int temporal_res = func_ptr(a, b);
  return temporal_res + c;
  /* dentro de esta funcion, no podemos conocer cual es el resultado de 
   ejecutar func_ptr(a, b), ya que no conocemos la funcion en especifico. 
   El apuntador podra senialar a cuaquier funcion que devuelva un entero,
   y reciba 2 enteros. Sera la funcion sum? o minus? o mult?. 
   En realidad puede ser cualquiera de las 3! */
}

/* Aqui solo tenemos un ejemplo mas de como podemos crear una funcion que recibe un apuntador y simplificar su sintaxis aprovechando el typedef que creamos anteriormente
generic_fun es un tipo de dato apuntador a funcion, que recibe 2 enteros y devuelve un entero. func_ptr es nuestra variable de este tipo */
int func_c2(two_operand_func func_ptr, int a, int b, int c)
{
  int temporal_res = func_ptr(a, b);
  return temporal_res + c;
}

/* triples, es una funcion que recibe 3 enteros. Su firma por lo tanto NO es compatible con sum, minus ni mult. Intenta asignar su direccion a uno de nuestros apuntadores genericos y obtendras un error de "tipo de dato incompatible" */
int triples (int a, int b, int c)
{
  return a+b+c;
}

void func_pointers_theory()
{
  int (*fun_ptr) (int, int);

  fun_ptr = sum; 

  //the name of he function represent the address, no need to put &
  //but that works too.
  int(*ptr2)(int, int) = &minus;                        
  int(*foo)(int, int) = mult;

  two_operand_func func = mult;
                              
  fun_ptr(2,4);
  ptr2(4,2);
  foo(5,5);
  func(6,6);    // created with typedef


  printf("==============\n");
  getchar();
                                          //a  b  c
  printf("result = %d\n", func_c(ptr2, 5, 5, 6));

  /*what you CAN DO:
  reuse the pointer: */
  getchar();
  ptr2 = mult;                             //a b  c
  printf("result = %d\n", func_c(ptr2, 5, 5, 6));

  /*what you CAN'T DO:
  assign a function with a different signature to ptr;*/
  //ptr2 = triples;      //because types are incompatible

  printf("======= array of functions =======\n");
  getchar();
  two_operand_func functions[3];

  functions[0] = sum;
  functions[1] = mult;
  functions[2] = minus;
  //
  for(int x = 0 ; x < 3; x++)
    functions[x](x,x);
  
}

int main()
{
  func_pointers_theory();
  return 0;
}