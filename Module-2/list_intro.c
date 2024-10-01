#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int num;
  struct node * next;
} node;

node * create_node(int num)
{
  node * new_node = (node *)malloc(sizeof(node));
  new_node->next = NULL;
  new_node->num = num;
  return new_node;
}

void static_node_example()
{
  node n1, n2, n3;
  n1.num = 1;
  n1.next = &n2;

  n2.num = 2;
  n2.next = &n3;

  n3.num = 3;
  n3.next = NULL;

  printf("Node 1 [%p] num = %d, next = %p\n", &n1, n1.num, n1.next);
  printf("Node 2 [%p] num = %d, next = %p\n", &n2, n2.num, n2.next);
  printf("Node 3 [%p] num = %d, next = %p\n", &n3, n3.num, n3.next);
  printf("\n");
}

void dynamic_node_example()
{
  node * n1 = create_node(1);
  node * n2 = create_node(2);
  node * n3 = create_node(3);

  n1->next = n2; 
  n2->next = n3;
  //El nodo 3, next ya apunta a null, porque create_node hace eso
  
  printf("List = %d -> %d -> %d\n", n1->num, n2->num, n3->num);

  /* EJERCICIO 1, imprimir toda la lista de forma mas inteligente,
  (que sirva para N numero de nodos) */

  //Tips: Declara un apuntador o inicio de la lista
  node * tmp = n1;

  //Ahora que tmp = n1, puedes imprimir de tmp, hasta el final (n3)

  /* Algoritmo:
      Mientras el apuntador tmp no apunte a nada.
        Imprimir el numero de temporal
        Recorrer temporal al siguiente nodo 
  */


  /* EJERCICIO 2, agregar un nodo, al final de la lista, volver
  a imprimir para comprobar */
  node * n_ptr = create_node(10);

  
}

int main()
{
  //static_node_example();
  dynamic_node_example();
  
  return 0;
}