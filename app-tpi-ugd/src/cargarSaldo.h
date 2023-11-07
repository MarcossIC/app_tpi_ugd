//
// Created by usuario on 6/11/2023.
//

#ifndef APP_TPI_UGD_CARGARSALDO_H
#define APP_TPI_UGD_CARGARSALDO_H

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

int guardarCargaDeSaldo(struct CargaSaldo cargaSaldo);

#endif //APP_TPI_UGD_CARGARSALDO_H
