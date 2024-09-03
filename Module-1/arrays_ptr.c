#include <stdio.h>

void array_pointers_basics();

int main()
{
  array_pointers_basics();
}

void array_pointers_basics() //Arreglo de apuntadores
{
  printf(" = = = = = = = = = = = = = = = = = = = \n");
  int arr0[3] = {0,1,2};
  int arr1[3] = {3,4,5};
  int arr2[3] = {6,7,8};

  /* super basics, recordemos como movernos en un arreglo      
    simple de enteros usando apuntadores */
    
  //-Crear un apuntador al tipo de dato guardado
  int * int_pointer = NULL;
  //-apuntamos este apuntador al inicio del array de 2 formas:
  // a array &arr0[0]  o simplemente a arr0;
  int_pointer = arr0;

  //con artimetica de punteros podemos movernos de int en int
  printf("value arr0[0] = %d at addr %p\n", *int_pointer, int_pointer);
  int_pointer++;
  printf("value arr0[1] = %d at addr %p\n", *int_pointer, int_pointer);
  int_pointer++;
  printf("value arr0[2] = %d at addr %p\n", *int_pointer, int_pointer);

  getchar();

  /* Todo lo anterior se pudo hacer en un for si conocemos 
    el tamanio del arreglo (si fuera arreglo de chars, podemos 
    limitarnos por el caracter '\0') */
  int * iptr = arr2;
  for(int i = 0; i<3; i++, iptr++)
  {
    printf("value arr2[0] = %d at addr %p\n", *iptr, iptr);
  }

  /* y si queremos un arreglo de direcciones (de apuntadores?)*/
 
  iptr = arr2;
  int * ptr_array[3] = { arr0, &arr1[0], iptr};
  // { arr0, arr1, arr2}; o inicializarlo despues.

  printf("\n\nAddress of the original array: \n");
  for(int i = 0;i<3;i++)
  {
    printf("%p, %p, %d\n", &ptr_array[i], ptr_array[i], *ptr_array[i]);
  }
  printf("\n");

  getchar();

  // -------------  AQUI VIENE LO NUEVO!  (y ni tan nuevo) -----------

  int **dptr = ptr_array;
  printf("Address stored on pointer dptr:  \n");
  for(int i = 0;i<3;i++)
  {
    printf("%p - ", *dptr);   // why * y not dptr?
    printf("%d \n", **dptr);  
    dptr++;
  }
  printf("\n");
  getchar();
  
  /* Usemos solo la variable tipo doble apuntador dptr   
    dptr controla las "filas"    
    iptr controla las "columnas"
    En realidad la memoria "Es plana" y no existe el concepto de 
    filas y columnas que anteriormente habiamos usado para entender
    mas facilmente matrices (x,y) */
  
  dptr = ptr_array; 
  //int * ptr_array[3] = { arr0, &arr1[0], iptr};
  //int * iptr = arr2;
  int * int_ptr = NULL;
  
  printf("con uso de double pointer: ");
  for(int i = 0;i<3;i++)
  {
    int_ptr = *dptr;
    for(int x = 0; x<3; x++)
    {
      printf(" %d ",*int_ptr);
      int_ptr++;
    }
    dptr++;
  }
  printf("\n");  
  getchar();

  //  ---- lo mismo pero con corchetes ----
  printf("con corchetes: ");
  for(int i = 0;i<3;i++)
  {
    iptr = ptr_array[i];
    for(int x = 0; x<3; x++)
    {
      printf(" %d ", iptr[x]);
    }
  }
  printf("\n");
  getchar();

    //  ---- lo mismo pero de golpe y lineal, esto demuestra que toda
    // la memoria (estatica) es contigua ----
  printf("de corrido: ");
  int_ptr = *ptr_array;
  for(int i = 0;i<9;i++)
  {
    printf(" %d ",*int_ptr);
    int_ptr++;
  }
  printf("\n");
  getchar();
  
  // ---- la misma logica funciona con "strings", porque los 
  // strings no existen! son arreglos de caracteres:

  char classroom[][10] = {"Mateo", "Ikram", "Walls"};
  char * student = &classroom[0][0];

  // recuerda que el printf imprime todos los caracteres hasta el \0
  printf("student 1 = %s\n", student);

  char * c = student;
  for (int x = 0; x <= 9; x++)
  {
    printf("%c - ", *c);
    c++;
  }

  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;
  printf("%c - ", *c); c++;

  printf("\n============================\n");
  getchar();

  /* now with chars */ 
  char letters[5] = {'s', 'e', 'b', 'a', 's'};
  char name[4] = "ale";

  char *str[5] = {"edgar", name, "edith", "nacho", letters};
  //char *str[4] = {name name, name, name};
  char **str_ptr = str;

  
  for(int i=0; i<=4; i++)
  {
    printf("%s\n", *str_ptr);
    str_ptr++;
  }
  
  
}

