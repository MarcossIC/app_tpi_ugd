//
// Created by usuario on 6/11/2023.
//

#ifndef APP_TPI_UGD_CUENTA_H
#define APP_TPI_UGD_CUENTA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Cuenta{
    int id;
    char DNI[20];
    float saldo;
    int tipo;
};

int obtenerUltimoIdDeCuenta();
int guardarCuenta(struct Cuenta cuenta);
bool esUnaCuentaRegistrada(char* DNI, int idCuenta);
int actualizarSaldoCuenta(int idCuenta, int saldoExtra);
int buscarIdCuenta(char* DNI);

#endif //APP_TPI_UGD_CUENTA_H
