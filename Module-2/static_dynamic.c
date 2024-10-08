#include <stdio.h>
#include <stdlib.h>

int global_a = 100;
int global_b;

void prueba()
{
  printf("Hi, test function\n");
}

int main()
{
  //------------------------- PART 1----------------------------------
   printf("\033[0;0H\033[2J");
  printf("Hello world, lets see where everything lives\n\n");

  int s_int1 = 100;
  int s_int2;
  char * c1_ptr;
  char c_1;

  int var;
  printf("%d 00\n", var);
  
  c1_ptr = (char *)malloc(sizeof(char)*20);

  printf("\tAddress of global_a %p\n", &global_a);
  printf("\tAddress of global_b %p\n\n", &global_b);
  printf("\tAddress of s_int1 %p\n", &s_int1);
  printf("\tAddress of s_int2 %p\n", &s_int2);
  printf("\tAddress of c1_ptr [the pointer] %p\n", &c1_ptr);
  printf("\tAddress of c_1 %p\n", &c_1);
  printf("\tAddress of c1_ptr [the data it points to] %p\n\n", c1_ptr);

  printf("\tAddres of c_1ptr[0] %p\n",  &c1_ptr[0]);
  printf("\tAddres of c_1ptr[1] %p\n",  &c1_ptr[1]);
  printf("\tAddres of c_1ptr[2] %p\n\n",  &c1_ptr[2]);

  printf("\tmain %p\n", &main);
  printf("\tprueba %p\n", &prueba);

  
  getchar();
  printf("\033[0;0H\033[2J");
  
  //------------------------------ PART 2a----------------------------
  int * ptr = NULL;
  for (int i = 0; i<10; i++)
  {
    //ptr = malloc (64 * sizeof(int));

    
    //2d
    ptr = calloc (64, sizeof(int));
    printf("\t after allocation -> value = %d\n ", ptr[10]);
    
    ptr[10] = 5000;
   printf("Addr ptr %p  ptr[0] = %p - addr of ptr[10] = %p : value = %d\n",
            &ptr, &ptr[0], &ptr[10], ptr[10]);

    //2b
    //what if we free the memory? run and verify the results
    free(ptr);    
    printf("\t after freeing value = %d\n ", ptr[10]);
    getchar();
  }
  getchar();

  //------------------------------ PART 3 ------------------------------
  /* Podemos usar malloc y calloc para crear variables simples por ejemplo: */
  //Crea un entero;
  int * iptr = NULL;
  iptr = malloc(sizeof(int));

  //A partir de este punto, ya existe la memoria del entero, iptr apunta a ella
  *iptr = 10;
  printf("The value of the int that iptr points to is %d\n", *iptr);

  //Es como crear una variable, sin que la variable exista!
  //Si ya no queremos la variable:
  free(iptr);

  //A partir de este punto, ya "liberamos" de la memoria el espacio ocupado por nuestra
  //variable invisible. Podemos incluso reutilizar el apuntador
  iptr = &ptr[10];
  printf("iptr = %d\n", *iptr);

  //Cual es el ENORME problema que esto tiene?
  // Imaginemos que creamos una variable de esta forma:
  iptr = malloc(sizeof(int));

  //le damos valor:
  *iptr = 2022; 

  //reusamos el pointer para otra cosa ( o lo hacemos NULO)
  iptr = ptr;

  //Donde quedo mi 2022? como lo recupero??
  
  //MEMORY LEAK.
  // REGLA SUPER IMPORTANTE DE MEMORIA DIAMICA
  // POR CADA MALLOC/CALLOC debe de existir un FREE, o la memoria se va a perder.
  // Nunca le quiten el dedo (apuntador) a un bloque de memoria, o lo van a perder
  // y ni si quiera lo van a poder liberar.
  
}
