#ifndef APP_TPI_UGD_TRANSPORTES_H
#define APP_TPI_UGD_TRANSPORTES_H

#include <stdio.h>
#include "inputs.h"
#include "utilidades.h"
#include "validaciones.h"

struct Chofer {
    char DNI[10];
    char nombre[30];
    char apellido[30];
    char fechaNacimiento[11];
    char telefono[11];
    char email[100];
    int direccion;
};

struct Unidad {
    int idUnidad;
    char dniChofer[10];
    int turno; //Tarde, Mañana (1, 0)
    char marca[20];
    char modelo[20];
    int cantidadDeAsientos;
    int kilometraje;
    char fechaAlta[10];
    int aptoDiscapacitados; // Si, No (1, 0)
};

struct Chofer crearNuevoChofer();
struct Unidad crearNuevaUnidad();
int guardarChoferes(struct Chofer chofer);
int guardarUnidad(struct Unidad unidad);
int buscarUltimoIdUnidad();
bool choferExistePorDNI(const char* DNI);
bool unidadExistePorId(const int idUnidad);
int listarChoferes();
int listarUnidades();

#endif //APP_TPI_UGD_TRANSPORTES_H

