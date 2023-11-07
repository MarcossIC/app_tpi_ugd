#include <stdio.h>
#include "user.h"
#include "utilidades.h"

void clearConsole();

void ejecutarApp();
int pantallaInicio();
int pantallaRegistrarUsuario();
int pantallaListarUsuarios();
int pantallaEspera();
void imprimirMensaje(const char* mensaje, int color);

int main() {
    ejecutarApp();
    return 0;
}

void ejecutarApp(){
    int pantalla = -1;
    do{
        fflush(stdout);

        if(pantalla == -1) {
            pantalla = pantallaInicio();
            clearConsole();
        } else if(pantalla == -2){
            pantalla = pantallaEspera();
            clearConsole();
        }else if(pantalla == 1) {
            pantalla = pantallaRegistrarUsuario();
        } else if(pantalla == 2) {
            pantalla = pantallaListarUsuarios();
        }
    } while(pantalla != 0);
    imprimirMensaje("GRACIAS POR ENTRAR", DEFAULT_COLOR);
}

int pantallaInicio(){
    int nuevaPantalla = 0;
    bool opcionEsValida = true;
    do{
        printf("****************************************************\n");
        printf("***** SISTEMA ELECTRONICO PARA TRANSPORTE SUBE *****\n");
        printf("************** Elija una opcion ********************\n");
        printf("*  1 - Registrar Usuario                           *\n");
        printf("*  2 - Consultar Saldo                             *\n");
        printf("*  3 - Cargar Saldo                                *\n");
        printf("*  4 - Usuar Tarjeta                               *\n");
        printf("*  5 - Usuario Billetera                           *\n");
        printf("*  6 - Gestion de transporte                       *\n");
        printf("*  0 - Salir                                       *\n");
        printf("*:");
        scanf("%d", &nuevaPantalla);
        int opcionesValidas[] = {1, 2, 3, 4, 5, 6,0, -99};
        opcionEsValida = encontrarCoincidencia(nuevaPantalla, opcionesValidas);
        if(!opcionEsValida) imprimirMensaje("LO SIENTO, PANTALLA NO ENCONTRADA", RED_COLOR);
    } while(!opcionEsValida);
    return nuevaPantalla;
}

int pantallaListarUsuarios(){
    printf("*******************************************************************************\n");
    printf("***************                 LISTA DE CUENTAS                     **********\n");
    printf("*******************************************************************************\n");

    int conteo = listarTodosLosUsuariosRegistrados();
    printf("*******************************************************************************\n");
    printf("                              GRACIAS POR VER                           \n");
    printf("                         Hay %d cuentas registradas                   \n", conteo);
    printf("*******************************************************************************\n");
    return -2;
}

int pantallaRegistrarUsuario(){
    printf("****************************************************\n");
    printf("*************** REGISTRO DE CUENTA *****************\n");
    printf("****************************************************\n");
    struct Usuario cuenta = crearNuevoUsuarioValido();
    printf("****************************************************\n");

    int error = guardarUsuario(cuenta);
    clearConsole();
    if(error == 1) imprimirMensaje("Error al crear el usuario. ", RED_COLOR);
    if(error == 0) imprimirMensaje("Usuario creado con exito. ", GREEN_COLOR);
    return -2;
}

int pantallaEspera(){
    int nuevaPantalla = 0;
    bool opcionEsValida = true;
    do{
        printf("*************    Que desea realizar?   *************\n");
        printf("* -1 - Continuar                \n");
        printf("*  0 - Salir                     \n");
        printf("*:");
        scanf("%d", &nuevaPantalla);
        int opcionesValidas[] = {0,-1, -99};
        opcionEsValida = encontrarCoincidencia(nuevaPantalla, opcionesValidas);
        if(!opcionEsValida) imprimirMensaje("LO SIENTO, PANTALLA NO ENCONTRADA", RED_COLOR);
    } while(!opcionEsValida);
    return nuevaPantalla;
}

void imprimirMensaje(const char* mensaje, int color) {
    setColorOutput(color);
    printf("****************************************************\n");
    printf("%s\n", mensaje);
    printf("****************************************************\n");
    resetColor();
}