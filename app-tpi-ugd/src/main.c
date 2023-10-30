#include <stdio.h>

#include "accounts.h"
#include <string.h>

void runApp();
void screen0();
int screenInit();
int screenRegisterAccount();
void screenEnd();

int main() {
    runApp();
    return 0;
}

void runApp(){
    int screen = -1;
    do{
        if(screen == -1) screen = screenInit();
        if(screen == 1) screen = screenRegisterAccount();

    } while(screen != 0);

    screenEnd();
}

int screenInit(){
    int updatePage = 0;
    printf("****************************************************\n");
    printf("***** SISTEMA ELECTRONICO PARA TRANSPORTE SUBE *****\n");
    printf("************** Elija una opcion ********************\n");
    printf("*  1 - Registrar Usuario                           *\n");
    printf("*  2 - Consultar Saldo                             *\n");
    printf("*  3 - Cargar Saldo                                *\n");
    printf("*  4 - Usuar Tarjeta                               *\n");
    printf("*  5 - User Billetera                              *\n");
    printf("*  6 - Gestion de transporte                       *\n");
    printf("*  0 - Salir                                       *\n");
    printf("*:");
    scanf("%d", &updatePage);
    return updatePage;
}

void screen3(){

}

int screenRegisterAccount(){

    printf("****************************************************\n");
    printf("*************** REGISTRO DE CUENTA *****************\n");
    printf("****************************************************\n");
    struct Account account = getRegisterValidInput();
    printf("****************************************************\n");

    int error = createUserAccount(account);
    printf("****************************************************\n");
    if(error == 1) printf("* Error al crear el usuario.                       *\n");
    else printf("* Te has registrado con exito.                     *\n");
    printf("****************************************************\n");
    return -1;
}

void screenEnd(){
    printf("****************************************************\n");
    printf("*************    GRACIAS POR ENTRAR    *************\n");
    printf("****************************************************\n");
}