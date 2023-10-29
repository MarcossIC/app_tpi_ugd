//
// Created by usuario on 28/10/2023.
//

#include "validateData.h"

bool isNameOrLastNameValid(char *nameOrLastname, char* type) {
    bool isNameOrLastNameValid = true;
    if (strlen(nameOrLastname) <= 3) {
        isNameOrLastNameValid =  false;
        printf("Error, El %s no puede ser menor a 3 caracteres.\n", type);
    }
    if (strcspn(nameOrLastname, "0123456789") < strlen(nameOrLastname)) {
        printf("Error, El %s no puede contener numeros.\n", type);
        isNameOrLastNameValid =  false;
    }

    return isNameOrLastNameValid;
}

bool isBirthDateValid(int day, int month, int year) {
    bool isBirthDateValid = true;

    if (year < 0) {
        printf("Error, Año no puede ser 0.\n");
        isBirthDateValid = false;
    }
    if (isBirthDateValid && calcUserAge(year) < 6) {
        printf("Error, Debes de tener mas de 6 años.\n");

        isBirthDateValid = false;
    }
    if (isBirthDateValid && month < 1 || month > 12) {
        printf("Error, Mes no puede ser menor a 1 o mayor 12\n");
        isBirthDateValid = false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    if(isBirthDateValid && !(day > 0 && day <= daysInMonth[month-1])){
        printf("Error, dia no valido.\n");
        isBirthDateValid = false;
    }

    return isBirthDateValid;
}

bool isDniValid(char *dni) {
    bool isDniValid = true;
    if (!(strlen(dni) < 12 && strlen(dni) >= 7)) {
        isDniValid =  false;
        printf("Error, El tamaño del dni no es valido.\n");
    }

    return isDniValid;
}

bool isAddressValid(char *address) {

    return true;
}

bool isCellphoneValid(char *cellphone) {

    return true;
}

int calcUserAge(int year){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;

    return currentYear - year;
}

bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}