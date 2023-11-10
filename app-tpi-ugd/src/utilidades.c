
#include "utilidades.h"

/**
 * Calcula la edad actual de la persona segun un año
 *
 * @param year Año de nacimiento
 *
 * @return Edad que tendria este año
 */
int calcularEdad(int year){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int currentYear = tm.tm_year + 1900;
    return currentYear - year;
}

/**
 * Ejecuta un comando para limpiar la consola segun el sistema operativo
 */
void clearConsole() {
    if (isWindowsOS()) system("cls");
    else system("clear");
}

const char* recuperarTipoBocaPago(const int tipo){
    const char buffer[50];
    if(tipo == 1) strcpy(buffer, "");
    if(tipo == 2) strcpy(buffer, "");
    if(tipo == 3) strcpy(buffer, "");
    if(tipo == 4) strcpy(buffer, "");
    if(tipo == 5) strcpy(buffer, "");
    if(tipo == 6) strcpy(buffer, "");
    return buffer;
}

void setColorOutput(int foregroundColor){
    if (isWindowsOS()) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, foregroundColor);
    } else {
        printf("\033[%d;%dm", foregroundColor);
    }
}

void resetColor() {
    if (isWindowsOS()) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    } else {
        printf("\033[0m");
    }
}

void imprimirMensaje(const char* mensaje, int color) {
    setColorOutput(color);
    printf("****************************************************\n");
    printf("%s\n", mensaje);
    printf("****************************************************\n");
    resetColor();
}