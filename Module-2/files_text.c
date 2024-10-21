#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* I/O Lectura de archivos:

Leer archivos, requeire siempre un file Handler. Este es un pointer del 
tipo de dato FILE. 

FILE * fp;
fp = fopen ("file.txt", "w+");

cuanto tenemos nuestro FILE ptr, debemos de abrir
el archivo en el modo correcto de lectura / escritura.
Al terminar de usar el archivo, debemos de cerrarlo con fclose()

Los modos soportados por fopen son:
        para texto                         | para modo binario
r   lectura texto                          | rb
w   escritura texto                        | wb
a   "append" escribe al final texto        | ab
r+  lectura y escritura (el archivo debe de existir)  | r+b o rb+
w+  crea un archivo vacio para lectura y escritura  | w+b o wb+
a+  abre el archivo para lectura y appending          | a+b o wb+

*/

typedef struct student
{
  char name[20];
  int grade;
} student;

student s_arr[10];
int num;

void create_students()
{
  char name[50];
  int i, ret;

  printf("Enter number of students: ");
  ret = scanf("%d", &num);

  for(i = 0; i < num; ++i)
  {
    printf("For student%d\nEnter name: ", i+1);
    ret = scanf("%s", s_arr[i].name);

    printf("Enter grade: ");
    ret = scanf("%d", &s_arr[i].grade);

    printf("\tCreated student Name: %s with Grade %d\n", 
      s_arr[i].name, s_arr[i].grade);
  }
}

/* Ejemplo para escribir con fprintf ... es una de las formas
mas faciles de escribir a un archivo de texto. Funciona igual que un printf
pero en lugar de enviar a pantalla, envia a un archivo.

fputc puede mandar caracter por caracter. (la verdad no es tan util)

*/
void fprintf_example()
{
  int i, ret;
  FILE *fptr;

  //w = write
  //a = append
  //Prueba cambiar entre w y a ....
  //"w" va a sobreescribir el archivo, "a" pondra el cursor
  //hasta el final y escribe ahi.

  fptr = (fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\files_student.txt", "w"));
  if(fptr == NULL)
  {
    printf("Error!");
    exit(1);
  }

  fprintf(fptr, "Students=%d\n", num); 
  for(i = 0; i < num; ++i)
  {
    printf("Writting... : \n");
    fprintf(fptr, "Name: %s\nGrade=%d\n", 
            s_arr[i].name, s_arr[i].grade);
 }
 fclose(fptr);
}



/* Ejemplo para leer desde texto, en esta funcion vemos el uso de :
   fgets = obtiene toda una linea de texto de golpe hasta encontrar
           salto de linea. 

  Podemos meter el fgets en un loop mientras que no devuelva NULL
  y cada llamada nos traera una linea completa. El buffer que recibe
  la lectura tiene que ser suficientemente grande, de no ser asi, leera
  hasta el tamanio del buffer

  Prueba cambiando el tamanio de name_r[20] a name_r[5]
*/

void fgets_example()
{
  char buffer[500];
  FILE *fptr;
  char * cret;

  printf("voy a leer ... \n");
  fptr = (fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\files_student.txt", "r"));
  cret = fgets(buffer, sizeof(buffer), fptr);   

  printf("la primer linea fue: %s\n", buffer);

  getchar();
  while(fgets(buffer, sizeof(buffer), fptr) != NULL)
  {
    printf("la linea contiene: %s", buffer);
    getchar();
  }
  fclose(fptr);
}
void fgetc_example()
{
  char c;
  FILE *fptr;
  printf("voy a leer ... \n");
  fptr = fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\files_students.txt", "r");
  if(fptr == NULL)
  {
    printf("File not found! Error!");
    exit(1);
  }
  
  do
  {
    c = fgetc(fptr);
    printf("lei: %c\n", c);
  }while (c != EOF); //END OF FILE
  fclose(fptr);
}

void fwrite_example()
{
  FILE *fptr;
  fptr = fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\student.data", "wb");
          //3
  fwrite(&num, sizeof(int), 1, fptr);
  for(int i=0; i<num; i++)
  {
    fwrite(&s_arr[i], sizeof(student), 1, fptr);
  }
  fclose(fptr);
}

void fread_example()
{
  FILE *fptr;
  fptr = fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\student.data", "rb");
  int num_elem, ret;
  student s;

  ret = fread(&num_elem, sizeof(int), 1, fptr);

  printf("Found %d students... \n", num_elem);

  for(int i = 0; i < num_elem; i++)
  {
    ret = fread(&s, sizeof(student), 1, fptr);
    printf("\tFound 1 student named %s with %d\n", s.name, s.grade);
  }
  /* NOTE, here we have only read the students, we reused the variable
  "s" to read them, but we have not saved them anywhere */

  fclose(fptr);
}


void fscanf_example()
{
  FILE *fptr;    //PATH
  fptr = fopen("C:\\Users\\JP - ITESO\\Documents\\ITESO\\Estructura de Datos O2024\\Lectura Archivos\\fscanf_ejemplo.txt", "r");

  char building;
  int capacity;
  char ret;
  int count = 0;

  while((ret = fscanf (fptr, "Edificio %c %d alumnos\n", 
                &building, &capacity))  !=  EOF)
  {
    count++;
    printf("%c=%d\n", building, capacity);
  };
  printf("Total of %d buildings found\n", count);
  fclose(fptr);
}

int main()
{
  int opc, ret;
  while(1)
  {
    printf("\n0) Create students to play with\n"
           "1) Write Students to plain text file \n"
           "2) Read from plain text file\n"
           "3) Read char by char example\n"
           "4) Write students to Binary file\n"
           "5) Read Binary file and extract students\n"
           "6) fscanf example\n");
    
    ret = scanf("%d", &opc);
    switch(opc)
    {
      case 0: create_students();
      break;
      case 1: fprintf_example();
      break;
      case 2: fgets_example();
      break;
      case 3: fgetc_example();
      break;
      case 4: fwrite_example();
      break;
      case 5: fread_example();
      break;
      case 6: fscanf_example();
      break;
    }
  }
  return 0;
}
