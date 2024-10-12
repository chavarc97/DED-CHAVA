#include <stdio.h>
#include <stdlib.h>

// Traete el codigo del STACK aqui, que necesitas hacerle para que
// funcione? Son muy pocos cambios.
typedef struct Stack
{
  /* data */
  char c;
  struct Stack *prev;
} Stack;

Stack *top_stack = NULL;
int counter = 0;

// prototypes
void push(char x);
char pop();
void isvalidformula(char *f);
void display();

int main()
{
  char formula1[30] = "aa()bb((c))(ddd((rr((a)a)))";
  char formula2[30] = "((a+b)-(z*d))";

  printf("Formula 1: %s\n", formula1);
  isvalidformula(formula1);
  getchar();

  printf("Formula 2: %s\n", formula2);
  isvalidformula(formula2);
  getchar();
}

// push node
void push(char x)
{
  Stack *prev = top_stack;
  Stack *new_n = (Stack *)malloc(sizeof(Stack));
  // assign the character to the new node
  new_n->c = x;
  // update the top
  new_n->prev = prev;
  top_stack = new_n;
  counter++;
}

// pop the node and return the char
char pop()
{
  Stack *old_top = top_stack;
  Stack *new_top = NULL;

  // remove the top
  char popped_node = old_top->c;
  new_top = old_top->prev;
  free(old_top);
  top_stack = new_top;
  return popped_node;
}

void isvalidformula(char *f)
{
  // step 1: clear the stack
  if (top_stack != NULL)
  {
    for (int i = 0; top_stack != NULL; i++)
    {
      pop();
    }
  }

  // check the formula
  for(int i = 0; f[i] != '\0'; i++) // iterate through the formula string until the end
  {
    if(f[i] == '(') // if the character is an open parenthesis, push it to the stack
    {
      push(f[i]);
    } else if (f[i] == ')') // if the character is a closing parenthesis, pop the stack
    {
      if(top_stack == NULL) // edge case: if the stack is empty, the formula is invalid
      {
        printf("Invalid formula\n");
        return;
      }
      pop(); // if the stack is not empty, pop the stack
    }
  }
  // after iterating through the formula, if the stack is empty, the formula is valid
  if(top_stack == NULL)
  {
    printf("Valid formula\n");
  } 
  else // but if the stack is not empty, the formula is invalid
  {
    printf("Invalid formula\n");
  }
}

void display() 
{
  Stack * nptr = top_stack;
  
  if (nptr == NULL)
  {
      printf("\nStack Underflow\n");
      return;
  }
  
  printf("The stack is \n");
  while (nptr != NULL)
  {
      printf("%c--->", nptr->c);
      nptr = nptr->prev;
  }
  printf("NULL\n\n");
  
}