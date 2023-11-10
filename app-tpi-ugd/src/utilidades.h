#ifndef APP_TPI_UGD_UTILIDADES_H
#define APP_TPI_UGD_UTILIDADES_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "validaciones.h"

#define BLACK_COLOR 0
#define SKYBLUE_COLOR 1
#define GREEN_COLOR 2
#define AQUAMARINE_COLOR 3
#define RED_COLOR 12
#define PURPLE_COLOR 5
#define YELLOW_COLOR 14
#define WHITE_COLOR 7
#define BLUE_COLOR 9
#define DARK_GREEN 10


int calcularEdad(int year);
void clearConsole();
void setColorOutput(int foregroundColor);
void resetColor();
const char* recuperarTipoBocaPago(const int tipo);
void imprimirMensaje(const char* mensaje, int color);

#endif //APP_TPI_UGD_UTILIDADES_H
