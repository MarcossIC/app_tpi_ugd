//
// Created by usuario on 28/10/2023.
//

#ifndef APP_TPI_UGD_USER_H
#define APP_TPI_UGD_USER_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Usuario{
    char nombre[50];
    char apellido[50];
    char dni[50];
    char direccion[50];
    char fechaNacimiento[11];
    char telefono[50];
    int tipo;
};

int guardarUsuario(struct Usuario user);
int listarTodosLosUsuariosRegistrados();
struct Usuario crearNuevoUsuarioValido();

#endif //APP_TPI_UGD_USER_H
