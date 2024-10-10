#include <stdio.h>
#include <stdlib.h>
/* UTILIZA EL CODIGO VISTO EN LAS DIAPOSITVAS EN CLASE PARA COMPLETAR
EL SIGUIENTE EJERCICIO */

/* El nodo */
typedef struct node
{
  int value;
  struct node *next;
} node;

/* Nuestro header se llama "header" y es una variable GLOBAL
   inicializada a NULL. Todas las funciones de este ejercicio
   van a considerar "header" como la cabecera de la unica lista
   que aqui existe.
   En la realidad, deben de existir muchas listas y las funciones
   deberian  de recibir la lista a la cual aplicar, pero eso lo veremos
   mas adelante  */

node *header = NULL; //<--- esta es nuestra primer lista ligada! :)

// Pendiente:
// void printlist( ...

// Pendiente:
// void add...

// Pendiente:
/*Funcion que inserta un nodo N despues de X
  Encuentra el primero nodo con valor X e inserta
  N inmediatamente despues ...

  Regresa 1 si si pudo insertar o 0 si no */

// int insert_after(..

// Pendiente:
/*Funcion que inserta un nodo N antes de X
  Encuentra el primero nodo con valor X e inserta
  N inmediatamente antes ...

  Regresa 1 si si pudo insertar o 0 si no */

// int insert_before(..

// Pendiente
/* Funcion para borrar el nodo que contiene N numero adentro */
// void delete(..

// Pendiente
/*Funcion para buscar un nodo que contiene N numero, si lo encuentra
  debera de imprimir la direccion donde vive, sino lo encuentra
  debera de imprimir textualmente "NULL" */

// prototypes
void print_list(node *h);
node *newNode(int n);
void add(node *n);
int insert_after(node *h, int n);
int insert_before(node *h, int n);
void delete(int n_val);
void search(int n);

int main()
{
  /* #1 :
  Crea una funcion newNode(n) que cree un nuevo node con valor n,
  y devuelva el puntero al nodo recien creado */

  /* #2:
  Utilizando esta funcion, crea un nodo nuevo para que actue como el primer
  elemento "header" de nuestra lista  */
  header = newNode(1);

  /* #3:
  Crea 5 nodos adicionales, para tener una lista total de 5 nodos
  perfectamente ligados entre si, codifica una funcion
  add() que reciba un nodo (existente, creado con newNode()) y
  agregue este nodo al final de la lista.

  Utiliza un ciclo FOR para llenar los 5 nodos */
  // se usaria asi:
  for (int x = 1; x <= 5; x++)
  {
    node *n = newNode(x + 1);
    add(n);
  }

  /* 4
  Crea una funcion de impresion, para imprimir toda la lista ligada,
  debera verse de esta forma:
    1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8 -> 9 -> 10 -> NULL
  */

  // se llamara asi:
  print_list(header);

  /* 5
  Crea un menu (en un while infinito), con las siguientes funcionalidades:

    0) agregar (agrega un nodo siempre al final)

    1) borrar (le pide la usuario un numero de la lista, para borrarlo)
        Considerar : borrar header
        Que el numero no exista : no debe de hacer nada.
    2) insertar despues de... (le pide al usuario, a partir de que numero quiere
  insertar) OJO. Aqui ya tienen que considerar : a) que pasa si quiero insertar
  en la raiz? b) que pasa si el numero no existe?

    3) inserta antes de... (igual que el punto 2, pero inserta antes)

    4) buscar (recibe un numero y devuelve un apuntador al nodo que lo contiene)
        Despues de buscar el elemento, imprimir el valor del nodo y su
  direccion.

    5) imprimir (imprime la lista de inicio a fin, como en el punto 4)

  El usuario debera de poder manipular toda la lista a placer.
  */

  int selection;
  int todel = 0;
  int toinsert = 0, tosearch = 0;
  int putafter = 0, putbefore = 0;
  node *new_node = NULL;
  int r = 0;

  while (1)
  {
    print_list(header);
    printf("Select option:\n 1) delete\n 2) insert after\n 3)insert before\n"
           " 4) search\n 5)print\n");
    printf("\topc:");
    r = scanf("%d", &selection);
    switch (selection)
    {
    case 1:
      printf("\tnumber to delete: ");
      r = scanf("%d", &todel);
      getchar();
      delete(todel);
      break;
    case 2:
      printf("\tnumber to insert: ");
      r = scanf("%d", &toinsert);
      getchar();
      printf("\tinsert after which node?: ");
      r = scanf("%d", &putafter);

      new_node = newNode(toinsert);
      if (!insert_after(new_node, putafter)) // == 0
      {
        // fail to insert, we need to free node
        printf("Failed to insert\n");
        free(new_node);
      }
      break;
    case 3:
      printf("\tnumber to insert: ");
      r = scanf("%d", &toinsert);
      getchar();
      printf("\tinsert after which node?: ");
      r = scanf("%d", &putbefore);

      new_node = newNode(toinsert);
      if (!insert_before(new_node, putbefore))
      {
        // fail to insert, we need to free node
        printf("Failed to insert\n");
        free(new_node);
      }
      break;
    case 4:
      printf("\tnumber to search: ");
      r = scanf("%d", &tosearch);
      getchar();
      search(tosearch);
      break;
    case 5:
      print_list(header);
      break;
    }
  }

  /* #6 Cuando ya tengas todo funcionando, has una copia de este archivo y
    llamalo: doublelinkedlist.c agrega el elemento :back a la estructura y crea
    una lista doblemente ligada, toda la funcionalidad tiene que persistir.

    La funcion imprimir, debera de imprimir la lista "de ida" usando el next y
    "de vuelta" usando el back y versea asi:

     1-> 2 -> 3 -> 4 -> ... 10 -> 9 -> 8 -> 7 -> ..... 1 -> NULL
  */
}

void print_list(node *h)
{
  node *tmp = h;
  printf("List = ");
  while (tmp != NULL)
  {

    printf("%d -> ", tmp->value);
    if (tmp->next == NULL)
    {
      printf("NULL");
    }
    tmp = tmp->next;
  }
  printf("\n");
}

node *newNode(int n)
{
  node *n_node = (node *)malloc(sizeof(node));
  n_node->next = NULL;
  n_node->value = n;
  return n_node;
}

void add(node *n)
{
  node *tmp = header;
  while (tmp->next != NULL)
  {
    tmp = tmp->next;
  }
  tmp->next = n;
}

int insert_after(node *n, int node_val)
{
  // Start from the header
  node *current = header;

  // Traverse the list to find the node with the value node_val
  while (current != NULL)
  {
    if (current->value == node_val)
    {
      // Insert the new node after the current node
      n->next = current->next;
      current->next = n;
      return 1; // Insertion successful
    }
    current = current->next;
  }

  // If the node with node_val is not found, return 0
  return 0;
}

int insert_before(node *n, int val)
{
  node *tmp = header;
  node *prev = NULL;
  // special case: insert before header
  if (header->value == val)
  {
    n->next = header;
    header = n; // Update the header pointer to the new node
    return 1;
  }
  // traverse the list to find the node with the value val
  while (tmp != NULL)
  {
    // Find the node with the provided value
    if (tmp->value == val)
    {
      prev->next = n;
      n->next = tmp;
      return 1;
    }
    // move to the next node
    prev = tmp; // keep track of the prev node
    tmp = tmp->next;
  }
  // node not found
  return 0;
}

void delete(int n_val)
{
  node *n_ptr = header;
  node *prev = NULL;

  // Special case if the node to delete is the first
  if(header->value == n_val)
  {
      prev = header; // keep track of the header
      header = header->next; // update the header to the next node
      free(n_ptr); // free n_ptr who is pointing to the header node
      return;
  }
  // Traverse the list to find the node to delete
  while (n_ptr != NULL)
  {
    if(n_ptr->value == n_val)
    {
      prev->next = n_ptr->next;
      free(n_ptr);
      return ;
    }
    prev = n_ptr;
    n_ptr = n_ptr->next;
  }
  // Node not found
  printf("Value not found\n");
  return ;

}

void search(int n)
{
  node *n_ptr = header;
  while (n_ptr != NULL)
  {
    if(n_ptr->value == n)
    {
      printf("Node value: %d, Node address: %p\n", n_ptr->value, &n_ptr);
      getchar();
      return;
    } 
    // move to the next node
    n_ptr = n_ptr->next;
  }
  
}