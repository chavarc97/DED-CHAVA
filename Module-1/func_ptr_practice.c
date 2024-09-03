#include <stdio.h>
#include <unistd.h>

/* This function is called when student has a non probatory grade */
void mad(char *name, int grade)
{
  printf("Hey %s, you are a Bad boy you better study\n"
         "your grade is %d!\n",
         name, grade);

  printf("Calling parents... \n");
  for (int x = 0; x < 3; x++)
  {
    printf("ring\n");
    sleep(2); // this funcion is inside unistd.h!!
  }
  printf("Thank you, go home.\n");
}

/* This is the regular funcion for any normal student with a normal grade */
void normal(char *name, int grade)
{
  printf("Hey %s, Your grade is %d!\n",
         name, grade);
}

/* Use this funcion to refer to the BEST of the BEST of your class */
void happy(char *name, int grade)
{
  printf("Congrats! %s, Your grade is %d you are the best!\n",
         name, grade);
}

/* RETO:
  El metodo main, debe de crear un arreglo de 3 puntos a funcion.
  Por convencion el arreglo en la posicion MAD, tendra el puntero a la llamada
  de funcion necesaria para la reprimenda (bad).
  En la posicion NORMAL tendra la llamada estandar (normal).
  Y en la posicion BEST tendra la llamada para los alumnos maravillos (happy).

Aprovecha los siguientes defines */
#define MAD 0
#define NORMAL 1
#define BEST 2

/* Completa la funcion "process student grade" para que reciba este arreglo
  de punteros a funcion, el string del alumno y su calificacion.
  La funcion process student grade deberia de analizar el contenido del alumno
  y seguir la siguiente logica:
    Para alumnos de 100, ejectuar la funcion guardada en la pos BEST.
    Para alumnos reprobados < 60, ejecutar la funcion guardada en pos MAD.
    Para todos los demas, la funcion NORMAL.
*/

//.. int process_student_grade(..

typedef void (*greeting)(char *name, int grade);
int process_student_grade(greeting *arr, char *student, int grade)
{
  if (grade == 100)
    arr[BEST](student, grade);
  else if (grade >= 60)
  {
    greeting func_ptr = arr[NORMAL];
    func_ptr(student, grade);
  }
  else if (grade <= 59)
  {
    greeting burro = arr[MAD];
    burro(student, grade);
  }
  return 0;
}

int main()
{
  greeting messages[3];
  messages[MAD] = mad;
  messages[NORMAL] = normal;
  messages[BEST] = happy;

  char student[10] = "Ken";
  int grade;
  printf("Enter your grade... ");
  int ret = scanf("%d", &grade);

  /* TODO call process_student_grade
   process_student_grade (....*/
  process_student_grade(messages, student, grade);

  return 0;
}