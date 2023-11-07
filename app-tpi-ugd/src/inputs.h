//
// Created by usuario on 6/11/2023.
//

#ifndef APP_TPI_UGD_INPUTS_H
#define APP_TPI_UGD_INPUTS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct CargaSaldo {
    char dni[50];
    int idCuenta;
    float monto;
    int bocaPago; // banco corrientes, santander rio, mercado pago, pago24, pago facil, rapipago, banco macro, banco nacion
    char fecha[20];
    char hora[10];
};

struct Cuenta{
    int id;
    char DNI[20];
    float saldo;
    int tipo;
};

int obtenerUltimoIdDeCuenta();
int guardarCuenta(struct Cuenta cuenta);
bool esUnaCuentaRegistrada(char* DNI, int idCuenta);
int guardarCargaDeSaldo(struct CargaSaldo cargaSaldo);
int actualizarSaldoCuenta(int idCuenta, int saldoExtra);


#endif //APP_TPI_UGD_INPUTS_H

