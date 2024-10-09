#include <stdio.h>
#include <stdlib.h>

int main()
{
/* Ejercicios Malloc / Free 
  * Ahora con estructuras */
  typedef struct Pollito
  {
    int id;
    char * name;
    int hp;
    
  } Pollito;

  /* 4, crea un pollito con ID 1*/
  Pollito * pollito1 = (Pollito *)malloc(sizeof(Pollito));
  pollito1->id = 1;
  Pollito * pollito2 = (Pollito *)malloc(sizeof(Pollito));
  pollito2->id = 2;
  Pollito * pollito3 = (Pollito *)malloc(sizeof(Pollito));
  pollito3->id = 3;
  Pollito * pollito4 = (Pollito *)malloc(sizeof(Pollito));
  pollito4->id = 4;
  /* 4.1, crea 3 pollitos mas! no pierdas la referencia a ellos, ponles el ID que queiras */
  

  /* 4.2 crea un arreglo de para guardar estos 4 pollitos existentes ...
     De que tipo de dato sera? ... tipo apuntador a pollito  
  */
  Pollito *granja[4];
  granja[0] = pollito1;
  granja[1] = pollito2;
  granja[2] = pollito3;
  granja[3] = pollito4;


  
  /* 4.3 imprime los pollitos usando el arreglo */
  for(int i = 0; i <4; i++)
  {
    printf("Pollito %d  ID: %d\n", i +1, granja[i]->id);
  }

  /*ya no quiero los pollitos, liberalos en la granja (TODOS)*/
  printf("Liberando pollitos\n");
  getchar();
  for(int i = 0; i <4; i++)
  {
    free(granja[i]);
  }
  printf("Pollitos liberados\n");
  for(int i = 0; i <4; i++)
  {
    printf("Pollito %d  ID: %d\n", i +1, granja[i]->id);
  }


  return 0;
} 