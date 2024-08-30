/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CLEAR printf("\033[0;0H\033[2J");

void ex01();
void ex02();
void ex03(char *);
void ex04();
int myLength(char *);
int isBinary(char *);

int main()
{
  CLEAR
  //  ========================ex01======================
  ex01();
  getchar();

  //  ========================ex02======================
  ex02();
  getchar();

  //  ========================ex03======================
  printf("=====================================================\n");
  printf("Exercise 03\n");
  char strArr[] = "HoLa MunDo!";

  printf("\n-- -- Before conversion -- --\n");
  for (int i = 0; i < strlen(strArr); i++)
  {
    printf("strArr[%d] = %c | %d\n", i, strArr[i], strArr[i]);
  }
  // call the 3dr exercise
  ex03(strArr);
  // Print the array result
  printf("\n-- -- After conversion -- --\n");
  for (int i = 0; i < strlen(strArr); i++)
  {
    printf("strArr[%d] = %c | %d\n", i, strArr[i], strArr[i]);
  }

  //  ========================ex04======================
  printf("=====================================================\n");
  printf("Exercise 04\n");
  ex04();

  return 0;
}

void ex01()
{
  /* Excerice 01:
  Create an array of 10 integers, set their value (whatever you want)
  Using pointer arithmetic and a for loop traverse and print all the array

  DO NOT USE BRACKETS [ ]

  Print both the value and the address.

  ie
    int array = [ 2 , 3 , 5 , 6]

    array[0] = 2 -> addr = 0x00001
    array[1] = 3 -> addr = 0x00004
    array[2] = 5 -> addr = 0x00008
    array[3] = 6 -> addr = 0x0000B
*/
  printf("=====================================================\n");
  printf("Exercise 01\n");
  int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int *arrPtr = arr;
  for (int i = 0; i < 10; i++, arrPtr++)
  {
    printf("arr[%d] = %d -> addr = %p\n", i, *arrPtr, arrPtr);
  }
}

void ex02()
{
  /* Excercise 02:
  Implement a function mylenght() that returns the size of the passed
  string (char array). DO NOT USE strlen(), use only pointer arithmetic.

  DO NOT USE BRACKETS [ ]

  TIP: all strings are array of chars, terminated by '\0' character.
*/
  printf("=====================================================\n");
  printf("Exercise 02\n");
  char str[] = "Hello World!";

  printf("The length of the string is: %d\n", myLength(str));
}

int myLength(char *str)
{
  int count = 0; // initialize the counter

  // check if the string traversing is not finished yet
  while (*str != '\0')
  {
    count++;
    str++;
  }
  return count;
}

void ex03(char *strArr)
{
  // need to substract 32 from each letter to convert it into capital letter
  // or add 32 to convert it to lower case

  while (*strArr != '\0')
  {
    if (*strArr > 'A' && *strArr <= 'Z')
    {
      *strArr += 32;
    }
    strArr++;
  }

}

void ex04()
{
  char inputStr[100];
  printf("Enter any text: ");
  fgets(inputStr, 100, stdin);
  inputStr[strcspn(inputStr, "\n")] = '\0';

  if (isBinary(inputStr))
  {
    printf("The string is binary\n");
  }
  else
  {
    printf("The string is not binary\n");
  }
}


int isBinary(char *inputStr)
{
  while(*inputStr != '\0')
  {
    if(*inputStr != '0' && *inputStr != '1')
    {
      return 0;
    }
    inputStr++;
  }

  return 1;
}
/* More practice excerises (similar to Ex02)

  NOTA :    No utilizar arreglos o corchetes dentro de
            ninguna de las 2 funciones.

  Excercise 03
  Implementa una funcion, que reciba por referencia un arreglo,
  recorra este arreglo y cambie cualquier mayuscula a minuscula,
  el arreglo se debe de imprimir de vuelta en el main  Tip: ASCII table

  Exercise 04
  Implementa una función isBinary que reciba una cadena de texto de consola
  y determine si está formada exclusivamente por dígitos binarios (0, 1).

*/
