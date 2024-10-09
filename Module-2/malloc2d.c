#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 4, crea un arreglo de 5 columnas y 3 filas:
    [1,2,3,4,5]
    [4,5,6,7,8]
    [9,10,11,12]

    Como haremos esto?
   */

int main()
{
  // crea la memoria para guardar el arreglo bidimencional:
  // primero las filas
  int **ptr = malloc(3 * sizeof(int *));

  // por cada fila, los 5 espacios para cada entero del arreglo
  for(int i = 0; i < 3; i++)
  {
    ptr[i] = malloc(5 * sizeof(int));
  }

  int count = 1;
  // rellenamos

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      ptr[i][j] = count;
      count++;
    }
  }
  // imprimimos

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 5; j++)
    {
      printf("[%d]", ptr[i][j]);
    }
    printf("\n");
  }
  /* Haz lo mismo pero ahora con un arreglo de chars para guardar:

  ["BIENVENIDO"]        len = 10 sin contar null
  ["A"]                 len = 1 sin contar null
  ["MEMORIA DINAMICA"]  len = 16 sin contar null

  */

  /* forma 1: en una primera matriz
    desperdiciando memoria : 3 x 16 */

  /* imprimimos, con aritemetica de punteros */

  /* no nos compliquemos */

  /* dibujemos como quedan ambas soluciones */

  /* como liberamos esto?  REGLA DE ORO, por cada malloc un FREE*/
}