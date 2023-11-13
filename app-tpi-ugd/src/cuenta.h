#ifndef APP_TPI_UGD_CUENTA_H
#define APP_TPI_UGD_CUENTA_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define TOPE 1000

struct Cuenta{
    int id;
    char DNI[10];
    float saldo;
    int tipo;
};

int obtenerUltimoIdDeCuenta();
int guardarCuenta(struct Cuenta cuenta);
int actualizarSaldoCuenta(int idCuenta, float saldoExtra, float *excedente);
int buscarIdCuenta(char* DNI);
struct Cuenta recuperarCuenta(const char* DNI);
float recuperarSaldo(const char* DNI);
void definirPrecio(float* precio, int tipoCuenta, int origen, int destino, int hora);

#endif //APP_TPI_UGD_CUENTA_H

