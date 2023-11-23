#ifndef APP_TPI_UGD_MOVIMIENTOS_H
#define APP_TPI_UGD_MOVIMIENTOS_H

#include <stdio.h>
#include <stdlib.h>
#include "inputs.h"
#include "utilidades.h"
#include "user.h"

struct Recargas{
    char DNI[10];
    int idCuenta;
    float monto;
    int bocaDePago;
    char fecha[11];
    int hora;
};

struct Movimiento{
    char DNI[10];
    int idCuenta;
    char telefono[11];
    int origen;
    int destino;
    float montoUtilizado;
    int idUnidad;
    char fecha[11];
    int hora;
    int esTarjeta;//  -  Diferenciar entre uso de trajeta y billetera (1, 0)
};

struct Movimiento crearNuevoMovimiento(int tipoDeUso);
int guardarRecarga(struct Recargas recarga);
int guardarMovimientos(struct Movimiento movimiento);
int listarMovimientosEntreFechas(const char* fechaInicio, const char* fechaFin);
void generarComrpobante(const char* name, struct Recargas recarga);
float contadorPorcentajePrimerTurno ();
int listarRecargaPorUsuario(const char *DNI);
int listarMovimientoPorUsuario(const char* DNI);
int buscarUnidadConMasViajes(const int mes);

#endif //APP_TPI_UGD_MOVIMIENTOS_H

