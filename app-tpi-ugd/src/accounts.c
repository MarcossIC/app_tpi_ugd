//
// Created by usuario on 28/10/2023.
//
#include "accounts.h"
#include "validateData.h"

char* getValidStringInput(char* inputName){
    bool inputValid = true;
    char input[50];
    fflush(stdin);
    do {
        printf("Ingresa su %s:", inputName);
        gets(input);
        inputValid = stringSizeGreaterThan(input, inputName, 50);
        if(inputValid && stringEquals(inputName, "dni"))
            inputValid = isDniValid(input);

        if(inputValid && (stringEquals(inputName, "nombre") ||  stringEquals(inputName, "apellido")))
            inputValid = isNamesValid(input, inputName);

        if(inputValid && stringEquals(inputName, "telefono"))
            inputValid = isCellphoneValid(input);

    } while(inputValid == false);
    return input;
}

char* getValidDate(char* dateName){
    bool isDateValid = true;
    int day, month, year;
    char date[20];
    do {
        printf("Ingresa su Fecha de %s:\n",dateName);
        printf("Dia:");
        scanf("%d", &day);
        printf("Mes:");
        scanf("%d", &month);
        printf("Año:");
        scanf("%d", &year);

        isDateValid = isValidDate(day, month, year);
        if(isDateValid && stringEquals(dateName, "nacimiento")) isDateValid = isGreaterThan(year, 6);
        sprintf(date, "%02d-%02d-%04d", day, month, year);
    } while(isDateValid == false);

    return date;
}

struct Account getRegisterValidInput(){
    struct Account account = {"", "", "", "", "", "", ""};
    char* input = getValidStringInput("nombre");
    strcpy(account.name, input);

    input = getValidStringInput("apellido");
    strcpy(account.lastName, input);

    input = getValidStringInput("dni");
    strcpy(account.dni, input);

    strcpy(account.cellphone, getValidStringInput("telefono"));

    strcpy(account.birthDay, getValidDate("nacimiento"));

    strcpy(account.address, getValidStringInput("direccion"));

    strcpy(account.type, getValidStringInput("tipo de cuenta"));

    return account;
}

int createUserAccount(struct Account account) {
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

bool isDniValid(char* dni){
    return isStringOnlyHasNumber(dni, "dni") && stringSizeIsEqualsTo(dni, "dni", 8);
}

bool isCellphoneValid(char* cellphone){
    return isStringOnlyHasNumber(cellphone, "telefono") && stringSizeIsEqualsTo(cellphone, "telefono", 10);
}

bool isNamesValid(char* name, char* nameType){
    return stringNotContainNumber(name, nameType) && stringSizeLessThan(name, nameType, 3);
}