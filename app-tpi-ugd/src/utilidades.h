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
#define DARK_GREEN_COLOR 10

struct Fecha {
    int dia;
    int mes;
    int anho;
};

int calcularEdad(int year);
void clearConsole();
void setColorOutput(int foregroundColor);
void resetColor();

void imprimirMensaje(const char* mensaje, int color);
int compararFechas(const char *firstDate, const char *secondDate);
const char* recuperarTipoBocaPago(const int tipo);
const char* recuperarTipoCuenta(const int tipo);
const char* recuperarDireccion(const int tipo);
struct Fecha desComponerFecha(const char* fecha);
int getCurrentYear();
void duplicarArchivo(const char *originalPath, const char *copyPath);
void borrarArchivo(const char* path);

#endif //APP_TPI_UGD_UTILIDADES_H

