
#include "validateData.h"

bool stringEquals(char* firstString, char* secondString){
    bool stringEquals = false;
    if (strcmp(firstString, secondString) == 0) {
        stringEquals = true;
    }
    return stringEquals;
}
bool stringSizeLessThan(char* string, char* stringName, int number){
    bool stringSizeLessThree = true;
    if (strlen(string) <= number) {
        stringSizeLessThree =  false;
        printf("Error, El %s no puede ser menor a %d caracteres.\n", stringName, number);
    }
    return stringSizeLessThree;
}

bool stringSizeIsBetween(char* string, char* stringName, int firstNumber, int secondNumber){
    bool stringSizeIsBetween = true;
    int lenght = strlen(string);
    if(lenght < firstNumber || lenght > secondNumber){
        printf("Error, El tamaño de %s no es valido, debe de estar entre %d y %d", stringName, firstNumber, secondNumber);
        stringSizeIsBetween = false;
    }
    return stringSizeIsBetween;
}

bool stringSizeGreaterThan(char* string, char* stringName, int number){
    bool stringSizeGreaterThan = true;
    if (strlen(string) >= number) {
        stringSizeGreaterThan =  false;
        printf("Error, El %s no puede ser mayor a %d caracteres.\n", stringName, number);
    }
    return stringSizeGreaterThan;
}

bool stringNotContainNumber(char* string, char* stringName){
    bool stringNotContainNumber = true;
    if (strcspn(string, "0123456789") < strlen(string)) {
        stringNotContainNumber =  false;
        printf("Error, El %s no puede contener numeros.\n", stringName);
    }
    return stringNotContainNumber;
}

bool isStringOnlyHasNumber(char *string, char* stringName){
    bool isStringOnlyHasNumber = true;
    int lenght = strlen(string);
    for (int i = 0; i < lenght; i++) {
        if (string[i] < '0' || string[i] > '9') {
            printf("Error, El %s solo puede tener numeros.\n", stringName);
            isStringOnlyHasNumber = false;
        }
    }
    return isStringOnlyHasNumber;
}

bool stringSizeIsEqualsTo(char *string, char* stringName, int size){
    bool stringSizeIsEqualsTo = true;
    if (!(strlen(string) == size)) {
        stringSizeIsEqualsTo = false;
        printf("Error, el tamaño del %s no puede ser distinto de %d",stringName, size);
    }
    return stringSizeIsEqualsTo;
}

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

bool isGreaterThan(int birthdayYear, int olderAge){
    bool isValidAge = true;
    if (calcUserAge(birthdayYear) < olderAge) {
        printf("Error, Debes de tener mas de %d años.\n", &olderAge);
        isValidAge = false;
    }
    return isValidAge;
}

bool isValidDate(int day, int month, int year) {
    bool isValidDate = true;

    if (year < 0) {
        printf("Error, Año no puede ser 0.\n");
        isValidDate = false;
    }
    if (isValidDate && month < 1 || month > 12) {
        printf("Error, Mes no puede ser menor a 1 o mayor 12\n");
        isValidDate = false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[1] = 29;
    }
    if(isValidDate && !(day > 0 && day <= daysInMonth[month-1])){
        printf("Error, el mes %d no tiene un dia %d.\n", month, day);
        isValidDate = false;
    }

    return isValidDate;
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