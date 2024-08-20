#include <stdio.h>
#define CLEAR printf("\033[0;0H\033[2J");
/* 
  Excercise 1 : swap
  Create a function that "swaps" the contents of two variables.
  It should receive two intengers, return nothing and after it execution
  whatever what inside one variable should be inside the other and viceversa 
  
*/
void swap(int *, int *);

/* Excercise 2 : blackjack

Create a blackjack function that:
  -receives 2 numbers and a FLAG (char)
  -returns 1 of the sum of the numbers is positive (greater than 0).
  -returns 0 if the sum of the numbers is negative.
  -Stores the sum of the two numbers in number2.
  -If the sum is 21, set the FLAG to = 'W' (winner)

   IN  IN/OUT  OUT
 (num1, num2, flag)

*/
int blackjack(int *, int *, char *);

int main()
{
  CLEAR
  /* Exercise 1:  swap num1 and num2 value */
  int num1 = 10;
  int num2 = 20;
  printf("Before swap: num1 = %d, num2 = %d\n", num1, num2);
  swap(&num1, &num2);
  printf("After swap: num1 = %d, num2 = %d\n", num1, num2);

  /* Exercise 2:  Blackjack 
    Call and test your program here */
  char flag;
  blackjack(&num1, &num2, &flag);
  printf("num1 = %d, num2 = %d, flag = %c\n", num1, num2, flag);
  
  return 0;
}

void swap(int *num1, int *num2)
{
  int temp = *num1;
  *num1 = *num2;
  *num2 = temp;
}

int blackjack(int *num1, int *num2, char *flag)
{
  *num2 = *num1 + *num2;
  if (*num2 == 21)
  {
    *flag = 'W';
    return 1;
  }
  else if (*num2 > 21)
  {
    *flag = 'L';
    return 1;
  }
  else if(*num2 > 0)
  {
    return 1;
  }
  else
    return 0;
}