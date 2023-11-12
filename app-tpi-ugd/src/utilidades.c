
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
    char* buffer = NULL;
    if(tipo == 1) buffer= strdup("Santander Rio");
    if(tipo == 2) buffer= strdup( "Banco Nacion");
    if(tipo == 3) buffer= strdup("Banco Corrientes");
    if(tipo == 4) buffer= strdup("Banco Macro");
    if(tipo == 5) buffer= strdup("Banco Galicia");
    if(tipo == 6) buffer= strdup("Personal Pay");
    if(tipo == 7) buffer= strdup("Mercado Pago");
    return buffer;
}

const char* recuperarTipoCuenta(const int tipo){
    char* buffer = NULL;
    if(tipo == 1) buffer= strdup("Normal");
    if(tipo == 2) buffer= strdup( "Boleto Estudiantil.");
    if(tipo == 3) buffer= strdup("Beneficio Discapacidad.");
    if(tipo == 4) buffer= strdup("Beneficio Anciano.");
    if(tipo == 5) buffer= strdup("Beneficio por ex combatiente de malvinas.");
    return buffer;
}

const char* recuperarDireccion(const int tipo){
    char* buffer = NULL;
    if(tipo == 1) buffer= strdup("Posadas.");
    if(tipo == 2) buffer= strdup( "Calendario.");
    if(tipo == 3) buffer= strdup("Beneficio Discapacidad.");
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

int compararFechas(const char *fechaUno, const char *fechaDos) {
    return strcmp(fechaUno, fechaDos);
}

struct Fecha desComponerFecha(const char* fecha){
    struct Fecha fechaS = {0,0,0};
    sscanf(fecha, "%d-%d-%d", &fechaS.anho, &fechaS.mes, &fechaS.dia);
    return fechaS;
}