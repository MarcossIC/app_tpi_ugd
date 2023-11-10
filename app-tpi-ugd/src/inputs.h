#ifndef APP_TPI_UGD_INPUTS_H
#define APP_TPI_UGD_INPUTS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilidades.h"
#include "validaciones.h"

void escribirStringValido(const char* nombreInput, char* input);
void escribirFechaValida(const char* dateName, char* date);
int escribirEnteroValido(const char* prompt);
float escribirNumeroDecimalValido(const char* prompt);
int recuperarHoraActual();
void recuperarFechaActual(char* date);
float escribirMontoValido(const char* prompt, float limite, float minimo);

#endif //APP_TPI_UGD_INPUTS_H

