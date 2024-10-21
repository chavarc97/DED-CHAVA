#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* I/O Lectura de archivos:
 */

FILE *fptr;
FILE *fout;

/* Abre el archivo ventas.txt */
/* Lee linea por linea los consumos por dia:


  dia 5 ventas $100.50 articulos 15
  dia 6 ventas $210.99 articulos 21
  ..

*/
/* Calcula el costo promedio por articulo por dia y escribelo
    en OTRO ARCHIVO (ventas_promedio.txt),
    cada linea debera quedar asi:

    PROMEDIOS DEL MES
    dia 5 promedio $6.7
    dia 6 promedio $10.04
    ..
  */
/* Al terminar de escribir en ventas_promedio.txt, vuelve
    a ventas.txt y escribe en una linea nueva la leyenda:
    PROMEDIOS ESCRITOS EN ventas_promedio.txt
    el archivo debera de quedar asi...

    ...
    dia 9 ventas $1200 articulos 150
    dia 19 ventas $200 articulos 50
    PROMEDIOS ESCRITOS EN ventas_promedio.txt
  */

int main()
{
  char line[100];
  int dia, articulos;
  float ventas, promedio;

  fptr = fopen("./ventas.txt", "r");
  if (fptr == NULL)
  {
    printf("File not found! Error!");
    exit(1);
  }
  // Abre el archivo de promedios para escritura
  fout = fopen("./ventas_promedio.txt", "w");
  if (fout == NULL)
  {
    printf("¡Error al crear archivo ventas_promedio.txt!\n");
    fclose(fptr);
    exit(1);
  }

  // Escribe el encabezado en el archivo de promedios
  fprintf(fout, "PROMEDIOS DEL MES\n");

  // Lee cada línea del archivo de ventas
  while (fscanf(fptr, "dia %d ventas $%f articulos %d\n",
                &dia, &ventas, &articulos) == 3)
  {
    // Calcula el promedio por artículo
    promedio = ventas / articulos;

    // Escribe el promedio en el archivo de salida
    fprintf(fout, "dia %d promedio $%.2f\n", dia, promedio);
  }

  // Cierra el archivo de promedios
  fclose(fout);

  // Reabre el archivo de ventas en modo append
  fclose(fptr);
  fptr = fopen("./ventas.txt", "a");
  if (fptr == NULL)
  {
    printf("¡Error al reabrir ventas.txt!\n");
    exit(1);
  }

  // Agrega la leyenda al final
  fprintf(fptr, "\nPROMEDIOS ESCRITOS EN ventas_promedio.txt\n");

  // Cierra el archivo
  fclose(fptr);

  printf("Proceso completado exitosamente.\n");

  return 0;
}
