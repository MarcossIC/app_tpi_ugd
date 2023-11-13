#ifndef APP_TPI_UGD_INPUTS_H
#define APP_TPI_UGD_INPUTS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "validaciones.h"

void escribirStringValido(const char* nombreInput, char* input);
void escribirFechaValida(const char* dateName, char* date);
int escribirEnteroValido(const char* prompt, bool esBinario);
float escribirNumeroDecimalValido(const char* prompt);
int recuperarHoraActual();
void recuperarFechaActual(char* date);
int getCurrentYear();
float escribirMontoValido(const char* prompt, float limite, float minimo);
int escribirDireccionValida(const char* nombreDireccion);

#endif //APP_TPI_UGD_INPUTS_H

