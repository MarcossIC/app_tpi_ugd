#ifndef APP_TPI_UGD_USER_H
#define APP_TPI_UGD_USER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "inputs.h"

struct Usuario{
    char nombre[50];
    char apellido[50];
    char DNI[10];
    char direccion[50];
    char fechaNacimiento[11];
    char telefono[11];
    int tipo;
};

int guardarUsuario(struct Usuario user);
int listarTodosLosUsuariosRegistrados();
struct Usuario crearNuevoUsuarioValido();
bool usuarioExistePorDNI(const char* DNI);

struct Usuario recuperarUsuario(char *DNI);

#endif //APP_TPI_UGD_USER_H
