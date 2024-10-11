#include <stdio.h>
#include <stdlib.h>

/* OJO Todo este stack, funciona solo con numeros enteros, ya que 
el nodo del Stack guarda un valor entero. En el proximo parcial
veremos como mejorar esto y generalizarlo utilizando un 
TDA (Tipo de dato abstracto) */

// Estructura para crear un stack_node, esta tendra el previous node
typedef struct stack_node {
    int info;
    struct stack_node *prev;
}stack_node;

/* STACK GLOBAL */
stack_node *stack_top = NULL;
int count = 0;

// Operacion Push() para meter elementos al stack 
void push(int data) 
{
  // Initialize a new node and the old top node
  stack_node *old_top = stack_top;
  stack_node *n = (stack_node *)malloc(sizeof(stack_node)); // Allocate memory for the new node
  n->info = data; // Assign the data to the new node
  n->prev = old_top; // Assign the old top address to the new top_node->prev pointer
  stack_top = n; // Assign the pushed node as the new stack_top
  count++;
}

// Para esta version de stack de enteros, regresa -1 si no hay 
// nada que hacer pop
int pop() 
{
  if (stack_top == NULL)
  {
    printf("Stack Is Empty\n");
    return -1;
  }
  stack_node *old_top = stack_top;
  stack_node *new_top = NULL;

  // Remove the top element
  int data = old_top->info; // Store the top element so we can return it
  new_top = old_top->prev; // Assign the new top element to the element below the old top
  free(old_top); // Free the memory of the old top element
  stack_top = new_top; // Update the top_stack pointer to the new top element
  return data; // Return the deleted element
}

// Muestra los elementos actuales del stack
void display() 
{
  stack_node * nptr = stack_top;
  
  if (nptr == NULL)
  {
      printf("\nStack Underflow\n");
      return;
  }
  
  printf("The stack is \n");
  while (nptr != NULL)
  {
      printf("%d--->", nptr->info);
      nptr = nptr->prev;
  }
  printf("NULL\n\n");
  
}

int main() 
{
  int choice, value, ret;
  printf("\nSTACK:\n");
  while (1) 
  {
    printf("\n1. Push\n2. Pop\n3. Display\n4. Exit\n");
    printf("\n\tChoice : ");
    ret = scanf("%d", &choice);
    switch (choice) 
    {
      case 1:
        printf("\tEnter the value to insert: ");
        ret = scanf("%d", &value);
        push(value);
        break;
      case 2:
        printf("Popped element is :%d\n", pop());
        break;
      case 3:
        display();
        break;
      case 4:
        exit(0);
        break;
      default:
        printf("\nWrong Choice\n");
    }
  }
}