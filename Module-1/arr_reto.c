#include <stdio.h>

/* Reto arreglos, apuntadores a apuntandores, apuntadores a funcion
   y void * :

  Declara 2 arreglos de 5 enteros:
    [5, 4, 3 , 2, 1]
    [2, 2, 4,  4, 5]

  Guarda las direcciones iniciales de cada arreglo, en un arreglo nuevo.

  arr[0] -> debera guardar la direccion para llegar a [1, 2, 3, 4, 5]
  arr[1] -> la direccion del otro arreglo.

  Crea una funcion "process" que reciba 2 cosas (a y b):
    a)    Mediante un puntero void, debera de recibir el arreglo de arreglos
          (ambos arreglos, con un solo apuntador).
          OJO, recibe un void *, ninguna otra cosa

    b)    Un puntero a funcion a una rutina que :
            reciba un (1) numero y lo imprima en pantalla.
            Utiliza la funcion print_star para probarlo
          OJO, un function pointer, ninguna otra cosa.

  La funcion process debera entonces, imprimir utilizando la funcion dada,
  cada numero que se encuentra dentro de cada ambos arreglos.

  Prohibido usar corchetes :)

  Si lo quieren hacer en 2 etapas para mas facil y mejor entendimiento:

  ETAPA 1:  process recibe (el arreglo de arreglos, el puntero a funcion)

  ETAPA 2 : process reciboe (el void pointer , el puntero a funcion.
  )

  SUERTE!

*/

void print_star(int b)
{
  while (b--)
    printf("|*|");
  printf("\n");
}

void process(void *arr, void (*print)(int));

int main()
{

  int arr1[5] = {5, 4, 3, 2, 1};
  int arr2[5] = {2, 2, 4, 4, 5};

  int *arrPtr[2] = {arr1, arr2};



  process(arrPtr, print_star);

  return 0;
}

void process(void *arr, void (*print)(int))
{

  // create the double pointer to the array
  int **ptr_arr = arr;
  for(int i = 0; i < 2; i++)
  {
    /* 
    * Al apuntador le decimos que apunte al double pointer
    * Esto es para que podamos movernos en el arreglo de arreglos
    * es como si en el double pointer nos metieramos a la primera direccion de memoria
    * al volver a hacer otro apuntador como el de aqui abajo estamos accediendo
    * a la direccion donde se encuentran los arreglos 
    */
    int *ptr = *ptr_arr;
    for(int j = 0; j < 5; j++)
    {
      printf("Valor: %d\t", *ptr);
      print(*ptr);
      ptr++;
    }
    ptr_arr++;
  }
}