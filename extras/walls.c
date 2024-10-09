#include <stdio.h>
/*
  OJO: Solo codifica donde veas:
     TU CODIGO INICIA AQUI

        en esta seccion :) 
  
     TU CODIGO TERMINA AQUI 
  
  Expandir la lista ligada:

  El siguiente programa construye una lista de la siguiente forma:


  * L0:     1 -  5 - 7 - 9 -  6
  *         |        |
  * L1:     3        2
  *                  |
  * L2:              0

  Cada nodo, puede tener un hijo bajo el. 
 

  Imprimir la lista con la funcion provista "print" arroja lo siguiente:
  
  list : 1c 5 7c 9 6

  la c indica, que el nodo N tiene un hijo (no se imprime).
  Print, solo recorre la lista imprimiendo en L0.

  "Expandir la lista" debera convertir todos los nodos hijos de N, en nodos
  siguientes (a la derecha por el apuntador next)

  En el ejemplo dado, print debera de imprimir esto despues de expandir la lista:

   list : 1 3 5 7 2 0 9 6

  NOTA:  Solo los nodos en nivel 0 (L0) pueden tener elementos a la derecha (next).
    eg, lo siguiente no se permite:
    
  * L0:     1 -  5 - 7 - 9 -  6
  *         |        |
  * L1:     3 - 4    2   <---- el nodo 3, no debe tener un elemento nodo en next.
  *                  |
  * L2:              0

  se utiliza NULL como indicador de fin de lista, tanto en horizontal (next)
  como en vertical (down)

  Codifica solamente la funcion expand(). No toques el resto del programa.

  Esta es la salida correcta del programa:

  Antes de expand
  list : 1c 5 7c 9 6 
  list : 1 5c 10 
  list : 1c 8c 
  list : 10 
  Despues de expand
  list : 1 3 5 7 2 0 9 6 
  list : 1 5 2 10 
  list : 1 2 3 8 9 0 
  list : 10 
*/


/*globals NO TOCAR*/
typedef struct node
{
  int val;
  struct node *next;
  struct node *down;
} node;

/* NO TOCAR */
node node1, node2, node3, node4, node5, node6, node7, node8;
node *head;

node d1, d5, d2, d0;
node *head2;

node b1, b2, b3, b8, b9, b0;
node *head3;

node v1;
node *head4;

void build_list()
{
  /* No tocar, NETA no tocar :) */
  node1.val = 1; node1.down = &node6; node1.next = &node2;
  node2.val = 5; node2.down = NULL; node2.next = &node3;
  node3.val = 7; node3.down = &node7; node3.next = &node4;
  node4.val = 9; node4.down = NULL; node4.next = &node5;
  node5.val = 6; node5.down = NULL; node5.next = NULL;
  node6.val = 3; node6.down = NULL; node6.next = NULL;
  node7.val = 2; node7.down = &node8; node7.next = NULL;
  node8.val = 0; node8.down = NULL; node8.next = NULL;
  head = &node1;

  d1.val=1; d1.next=&d5; d1.down=NULL;
  d0.val=10; d0.next=NULL; d0.down=NULL;
  d5.val=5; d5.next=&d0; d5.down=&d2;
  d2.val=2; d2.next=NULL; d2.down=NULL;
  head2 = &d1;

  b1.val=1; b1.next=&b8; b1.down=&b2;
  b2.val=2; b2.next=NULL; b2.down=&b3;
  b3.val=3; b3.next=NULL; b3.down=NULL;
  b8.val=8; b8.next=NULL; b8.down=&b9;
  b9.val=9; b9.next=NULL; b9.down=&b0;
  b0.val=0; b0.next=NULL; b0.down=NULL;
  head3 = &b1;

  v1.val=10; v1.next=NULL; v1.down=NULL;
  head4 = &v1;
}

/* traverses thru next only, prints "c" if has child 
   NO TOCAR */
void print(node *header)
{
  node * tmp = header;
  printf("list : ");
  while(tmp != NULL)
  {
    printf("%d%s ", tmp->val, (tmp->down) ? "c":"");
    tmp = tmp->next;
  }
  printf("\n");
}

void expand(node  *h)
{
  /* TU CODIGO INICIA AQUI */
  node *tmp = h;
  while(tmp != NULL)
  {
    if(tmp->down != NULL)
    {
        node *tmp2 = tmp->down; // initialize a new tmp pointer to tmp->down
        // integrate child into the main list
        while (tmp2->next != NULL)
        {
          tmp2 = tmp2->next; // move to the last node of the child
        }
        tmp2->next = tmp->next; // connect the last node of the child to the next node of the main list
        tmp->next = tmp->down;  // connect the child to the main list
        tmp->down = NULL;
    }
    tmp = tmp->next;  // move to the next node in the main list
  }
  /* TU CODIGO TERMINA AQUI */
}

int main()
{
  build_list();

  printf("Antes de expand\n");
  print(head);
  print(head2);
  print(head3);
  print(head4);
  
  expand(head);
  expand(head2);
  expand(head3);
  expand(head4);

  printf("Despues de expand\n");
  print(head);
  print(head2);
  print(head3);
  print(head4);

}