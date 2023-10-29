//
// Created by usuario on 28/10/2023.
//
#include "accounts.h"
#include "validateData.h"
#include <stdio.h>

int uiRegister(){
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
    return 1;
}
//

struct Account getRegisterValidInput(){
    struct Account account = {"", "", "", "", "", "", ""};
    int day, month, year;
    bool nameValid = false;
    bool lastNameValid = false;
    bool birthDateValid = false;
    bool dniValid = false;
    bool addressValid = false;
    bool cellphoneValid = false;
    do{
        if (!nameValid) {
            printf("Ingresa su nombre:");
            scanf("%s", account.name);
            nameValid = isNameOrLastNameValid(account.name, "nombre");
        }
        if (!lastNameValid) {
            printf("Ingresa su apellido:");
            scanf("%s", account.lastName);
            lastNameValid = isNameOrLastNameValid(account.lastName, "apellido");
        }
        if (!birthDateValid) {
            printf("Ingresa su Fecha de nacimiento:\n");
            printf("Dia:");
            scanf("%d", &day);
            printf("Mes:");
            scanf("%d", &month);
            printf("Año:");
            scanf("%d", &year);
            birthDateValid = isBirthDateValid(day, month, year);
            sprintf(account.birthDay, "%02d-%02d-%04d", day, month, year);
        }
        if (!dniValid) {
            printf("Ingresa su DNI:");
            scanf("%s", account.dni);
            dniValid = isDniValid(account.dni);
        }
        if (!addressValid) {
            printf("Ingresa su direccion:");
            scanf("%s", account.address);
            addressValid = isAddressValid(account.address);
        }
        if (!cellphoneValid) {
            printf("Ingresa su telefono:");
            scanf("%s", account.cellphone);
            cellphoneValid = isCellphoneValid(account.cellphone);
        }
    } while (!(nameValid && lastNameValid && birthDateValid && dniValid && addressValid && cellphoneValid));

    return account;
}

int createUserAccount(struct Account account){
    FILE* userFile = fopen("assets/Users.dat", "a+b");
    int errors = 0;
    if (!userFile) {
        printf("Error, no se ha podido abrir el archivo.\n");
        errors = 1;
    }
    if(userFile){
        fwrite(&account, sizeof(struct Account), 1, userFile);
        fclose(userFile);
    }

    return errors;
}
