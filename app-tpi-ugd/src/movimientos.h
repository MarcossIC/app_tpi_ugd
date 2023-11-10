#ifndef APP_TPI_UGD_MOVIMIENTOS_H
#define APP_TPI_UGD_MOVIMIENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "utilidades.h"

struct Recargas{
    char DNI[10];
    int idCuenta;
    float monto;
    int bocaDePago;
    char fecha[11];
    char hora[10];
};

struct Movimiento{
    char DNI[10];
    int idCuenta;
    char telefono[11];
    char origen[20];
    char destino[20];
    float montoUtilizado;
    int idUnidad;
    char fecha[11];
    int hora;
    int esTarjeta;//Diferenciar entre uso de trajeta y billetera (1, 0)
};

struct Movimiento crearNuevoMovimiento(int tipoDeUso);
int guardarRecarga(struct Recargas recarga);
int guardarMovimientos(struct Movimiento movimiento);

#endif //APP_TPI_UGD_MOVIMIENTOS_H
