#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Ejercicio:
  Declara una estructura "vehicle" con los atributos "brand" y "model"
  Utiliza typedef para ahorrar lineas en la declaracion.
  ej.  "Honda", 2001

  En el main, crea (instancia) 4 Vehiculos.

  Crea una funcion "vehicle_set" que reciba la direccion de un vehiculo y haga
  set a sus valores (Marca y modelo) con datos pasados a la funcion.
  Inicializa asi 3 de tus vehiculos.

  ej.  vehicle_set(ptr, "Ford", 2020);
       vehicle_set(another, name1var, year);


  Para no olvidar el uso de estructuras, El 4to vehiculo inicializalo de forma
  regular sin utilizar la funcion anterior.

  Crea una funcion que reciba un apuntador a un vehiculo e imprima sus
  caracteristicas */

typedef struct Car
{
    int verified;
    char brand[100];
    int model;
} Car;

void vehicle_set(Car *car_ptr, char *brand, int model);
void print_vehicle(Car *);
int main()
{
    Car car1, car2, car3, car4;
    Car * c_ptr = &car1; // pointer to car1
    vehicle_set(c_ptr, "Ford", 2020);
    c_ptr = &car2;  // pointer to car2
    vehicle_set(c_ptr, "Chevrolet", 2019);
    c_ptr = & car3; // pointer to car3
    vehicle_set(c_ptr, "Toyota", 2018);


    // Initialize car4 without using the function vehicle_set
    c_ptr = &car4; // pointer to car4
    // set the values of car4 manually without using a pointer
    strcpy(car4.brand, "Nissan");
    car4.model = 2017;
    print_vehicle(c_ptr);

    return 0;
}

/**
 * The function `vehicle_set` sets the brand and model of a car and then prints the car's information.
 * 
 * @param car_ptr A pointer to a Car struct that will be modified with the provided brand and model.
 * @param brand The `brand` parameter is a character array that represents the brand of the car.
 * @param model The `model` parameter in the `vehicle_set` function is an integer that represents the
 * model of the car. It is used to set the model of the car pointed to by `car_ptr`.
 */
void vehicle_set(Car *car_ptr, char *brand, int model)
{
    strcpy(car_ptr->brand, brand);
    car_ptr->model = model;
    car_ptr->verified = 1;
    print_vehicle(car_ptr);
}   

/**
 * The function `print_vehicle` prints the brand and model of a car.
 * 
 * @param car The `car` parameter in the `print_vehicle` function is a pointer to a `Car` struct.
 */
void print_vehicle(Car *car)
{
    printf("Car brand: %s \t", car->brand);
    printf("Car model: %d \t Verified: %s\n", car->model, car->verified ? "Yes" : "No");
}