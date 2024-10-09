#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* INSTRUCCIONES GENERALES, COMIENZA LEYENDO ESTE ARCHIVO
DESDE EL METODO MAIN */
#define FARMSIZE 10  

typedef struct pollito
{
  int id;
  int hp;
  /* Imagina que otros 4k de datos viven aqui
    pollito DNA sequence
    pollito Health Records
    pollito's 
    pollito's color RGB (red , green , blue)
  */
  int DNA[10000];
  
} pollito;

pollito * create_pollo(int id)
{
  pollito * new_pollo = (pollito *)malloc(sizeof(pollito));
  new_pollo->id = id;
  new_pollo->hp = rand() % 100;
  return new_pollo;
}


void add_pollo(pollito **farm)
{
  for(int i=0; i < FARMSIZE; i++)
  {
    if(farm[i] == NULL)
    {
      printf("Pollito added at slot [%d]\n", i);
      farm[i] = create_pollo(i);
      return; 
    }
  }
  //Si llegamos aqui, no hubo nada que reemplazar
  printf("The farm was healthy :)");
}

void print_all(pollito ** farm, int farm_size)
{
  /*TAREA #2 ... 
  No es buena idea acceder a elementos que aun no existen,
  Encuentra una manera de escribir "FREE" si el slot
  del pollito en la farm se encuentra disponible 
  
  /* Algo asi:
  
     = = WELCOME TO THE FARM = =
    [0] : Pollito with ID 0 / HP 100
    [1] : FREE
    [2] : FREE
    [3] : Pollito with ID 3 / HP 70 */

  
  printf("\n = = = = WELCOME TO THE FARM = = = =\n");
  pollito * p = NULL; 
  for(int i=0; i < farm_size; i++)
  {
    printf("[%d] : ", i);
    
    //p = *farm;
    if(farm[i] == NULL)
    {
      printf("FREE\n");
    }
    else
    {
      printf("Pollito with ID %d / HP %d\n", farm[i]->id, farm[i]->hp);
    }
  }
  printf(" = = = = = = = = E N D = = = = = = = = = \n");
}

void free_weak(pollito *farm, int num)
{
  if (farm == NULL)
  {
    return;
  }
  if(farm->hp <= num)
  {
    free(farm);
    farm = NULL;
  }
}

int main()
{
  srand (time(NULL));


  
  pollito farm_test[50];
  pollito * pfarm_test[50];
  pollito * ppollo;
  
  //size of pollito 
  printf("One pollito is : %ld bytes\n", sizeof(pollito));
  printf("One pollito ptr is : %ld bytes\n", sizeof(ppollo));
  printf("The farm is : %ld MEGABYTES\n", sizeof(farm_test)/1024/1024);
  printf("The farm is : %ld bytes (2k)\n", sizeof(pfarm_test));
  printf("The farm is 4608 times smaller! in memory\n");
  getchar();
 
  

  /* Paso 1: Crearemos una funcion para crear pollitos, recibe el
  ID del pollito
     Que se pueda usa asi:
     pollito * p = create_pollo(10);

  */   

  // printf("We have dynamically created 1 pollito with id = %d\n", p->id);

  /* Paso1 : Vamos a crear la granja usando memoria dinamica. Para esto, 
  nuestra granja sera un arreglo de punteros a pollito. Tantos pollitos
  como se defina en FARMSIZE */
  
  /* Primero, reservamos memoria contigua para el arreglo de punteros */ 
  pollito ** farm = (pollito **) malloc(sizeof(pollito *) * FARMSIZE);

  /* Muy bien, este punto, ya tenemos la memoria lista:
    farm = [ * ,  *  , *  , .... ] 
             |    |    |
             @    #    $

    pero todos los punteros apuntan a espacios de memoria que 
    contienen basura. Esto puede ser peligroso. */

  /*TAREA #1 Inicializa todos los pointers de pollitos del arreglo a NULL,
  para poder saber que espacios de nuestro granero, estan disponibles */
  for(int i=0; i < FARMSIZE; i++)
  {
    farm[i]=NULL;
  }
  /* Ya que inicializamos el arreglo de punteros, podemos ir creando 2 pollitos */
  // POLLITO ID 0, HP 100
  farm[0] = malloc(sizeof(pollito));
  farm[0]->id = 0;
  farm[0]->hp = 100;

  // POLLITO ID 1, HP 99
  pollito * p_ptr;
  
  farm[1] = malloc(sizeof(pollito));
  p_ptr = farm[1];
  p_ptr->id = 1;
  p_ptr->hp = 99;

  

  // Veamos como se ve nuestr granja.
  print_all(farm, FARMSIZE);
  //Exploto? Revisa la TAREA #2 dentro de la funcion print_all
  
  /* step two, for each ptr, we need another malloc */

  for(int x = 2; x < FARMSIZE; x++)
  {
    farm[x] = create_pollo(x);
  }
  

  /* print all the pollitos using a function that receives
     the array */
  print_all(farm, FARMSIZE);


  //TAREA #3
  //No nos gustan los pollitos debiluchos, libera todos los pollitos
  //cuyos health points sean <= 35
  //
  free_weak(farm, 35);


  //TAREA #4
  //Imprime toda la granja nuevamente, para verificar que los pollitos
  //debiles, ya fueron convertidos en Nuggets
  //Si ya arreglaste el punto "TAREA #2" ya deberias de ver "FREE"
  //en todas las posiciones donde se borro un pollito
  print_all(farm, FARMSIZE);

  //TAREA #5
  //Como nuestra granja quedo incompleta, necesitamos volver a llenarla 
  //con pollitos nuevos. Pero va a ser muy problematico ir buscando donde
  //hay "slots" libres para guardarlos.
  
  //Crea una funcion que se llame "add_pollo" que reciba la granja, encuentre el
  //primer lugar disponible donde recrear un pollito y lo ponga en su lugar.
  //Ojo el ID debe de corresponder al slot correcto.
  //Cada llamada a "add_pollo" hace refill a un pollito.
  //
  add_pollo(farm);
  add_pollo(farm);

  print_all(farm, FARMSIZE);

  //TAREA #6.
  //Es una lata llamar la funcion add_pollo tantas veces, ademas no sabemos
  //cuantas se necesitan. Agrega un contador a la granja, para llevar un count
  //de cuantos pollos se encuentran en ella.
  //Una vez que tengas el contador, utiliza un ciclo while para rellenar
  //todos los pollitos de golpe.
  int count = 0;
  for(int i=0; i < FARMSIZE; i++)
  {
    if(farm[i]!=NULL)
      count++;
  }
  while(count < FARMSIZE)
  {
    add_pollo(farm);
    count++;
  }
  print_all(farm, FARMSIZE);
  

  //TAREA #7
  /* Destruye toda la granja, cuantos FREEs se necesitan? */
  for(int i=0; i < FARMSIZE; i++)
  {
    if(farm[i]!=NULL)
      free(farm[i]);
  }
  //free(farm);
  print_all(farm, FARMSIZE);

  
}