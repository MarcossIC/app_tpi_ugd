#include <stdio.h>

#include "accounts.h"
#include <string.h>

void runApp();
void screenEnd();
int screenInit();
int screenRegisterAccount();
int screenViewAccounts();

int main() {
    runApp();
    return 0;
}

void runApp(){
    int screen = -1;
    do{
        fflush(stdout);

        if(screen == -1) {
            screen = screenInit();
            system("cls");
        } else if(screen == 1) {
            screen = screenRegisterAccount();
            system("cls");
        } else if(screen == 2) {
            screen = screenViewAccounts();
            system("cls");
        }
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

int screenViewAccounts(){
    printf("****************************************************\n");
    printf("*************** LISTA DE CUENTAS *****************\n");
    printf("****************************************************\n");

    int counting = listAllRegisteredAccounts();
    printf("****************************************************\n");
    printf("*                 GRACIAS POR VER                  *\n");
    printf("             Hay %d cuentas registradas            \n", counting);
    printf("****************************************************\n");
    return -1;
}

int screenRegisterAccount(){
    printf("****************************************************\n");
    printf("*************** REGISTRO DE CUENTA *****************\n");
    printf("****************************************************\n");
    struct Account account = getAccountValidInput();
    printf("****************************************************\n");

    int error = saveAccount(account);
    printf("****************************************************\n");
    if(error == 1) printf("* Error al crear el usuario.                       *\n");
    if(error == 0) printf("* Te has registrado con exito.                     *\n");
    printf("****************************************************\n");
    return -1;
}

void screenEnd(){
    printf("****************************************************\n");
    printf("*************    GRACIAS POR ENTRAR    *************\n");
    printf("****************************************************\n");
}

/* CARGA SALDO
    - Validar que la cuenta exista
    - Guardar recarga

 */


