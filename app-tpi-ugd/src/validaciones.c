#include "validaciones.h"

/**
 * Comprueba si dos Strings son iguales
 *
 * @param firstString Primer string a comprar
 * @param secondString Segundo string a comparar
 *
 * @return Booleano
 */
bool areStringsEqual(const char* firstString, const char* secondString){
    return strcmp(firstString, secondString) == 0;
}

/**
 * Comprueba si el tamaño del String es menor a una cifra pasada
 *
 * @param string Puntero al string que se desea comprobar
 * @param stringName Nombre del campo
 * @param minSize Rango minimo a comparar
 *
 * @return Booleano
 */
bool isStringLengthLessThan(const char* string, const char* stringName, int minSize){
    bool isStringLengthLessThan = true;
    if (strlen(string) >= minSize) {
        isStringLengthLessThan =  false;
        printf("Error, El %s no puede ser mayor a %d caracteres.\n", stringName, minSize);
    }
    return isStringLengthLessThan;
}

/**
 * Comprueba si el tamaño del String es mayor a una cifra pasada
 *
 * @param string Puntero al string que se desea comprobar
 * @param stringName Nombre del campo
 * @param maxSize Rango maximo a comparar
 *
 * @return
 */
bool isStringLengthGreaterThan(const char* string, const char* stringName, int maxSize){
    bool isStringLengthGreaterThan = true;
    if (strlen(string) <= maxSize) {
        isStringLengthGreaterThan =  false;
        printf("Error, %s no puede ser menor a %d caracteres.\n", stringName, maxSize);
    }
    return isStringLengthGreaterThan;
}

/**
 * Comprueba si el tamaño del String se encuentra entre dos rangos pasados
 *
 * @param string Puntero al string que se desea comprobar
 * @param stringName Nombre del campo
 * @param minSize Rango minimo para comparar
 * @param maxSize Rango maximo para comparar
 * @return Booleano
 */
bool isStringLengthBetween(const char* string, const char* stringName, int minSize, int maxSize){
    bool isStringLengthBetween = true;
    int lenght = strlen(string);
    if(lenght > minSize && lenght < maxSize){
        printf("Error, El tamanio de %s no es valido, debe de estar entre %d y %d\n", stringName, minSize, maxSize);
        isStringLengthBetween = false;
    }
    return isStringLengthBetween;
}


/**
 * Comprueba si el String no contiene numeros
 *
 * @param string Puntero al string a verificar
 * @param stringName Nombre del String
 * @return Booleano
 */
bool doesStringNotContainDigits(const char* string, const char* stringName){
    bool doesStringNotContainDigits = true;
    //En caso de tener false
    if (strcspn(string, "0123456789") < strlen(string)) {
        doesStringNotContainDigits =  false;//False, es que si contiene
        printf("Error, %s no puede contener numeros.\n", stringName);
    }
    return doesStringNotContainDigits;
}

/**
 * Comprueba que el String solo contenga numeros
 *
 * @param string Puntero al String a verificar
 * @param stringName Nombre del String
 * @return Booleano
 */
bool isStringOnlyHasNumber(const char *string, const char* stringName){
    bool isStringOnlyHasNumber = true;
    int value = 0;
    if (sscanf(string, "%d", &value) != 1) {
        printf("Error, El %s solo puede tener numeros.\n", stringName);
        isStringOnlyHasNumber = false;
    }
    return isStringOnlyHasNumber;
}

/**
 * Comprueba si el tamaño de un String es igual a uno pasado
 *
 * @param string Puntero al String
 * @param stringName Nombre del String
 * @param size Tamaño del String a comprobar
 * @return Booleano
 */
bool isStringLengthEqualTo(const char *string, const char* stringName, int size){
    bool isStringLengthEqualTo = true;
    if ( !areIntegersEqual(strlen(string), size)) {
        isStringLengthEqualTo = false;
        printf("Error, el tamanioo del %s no puede ser distinto de %d\n",stringName, size);
    }
    return isStringLengthEqualTo;
}

/**
 * Comprueba si dos enteros son igualles
 *
 * @param firstNumber Primero numero a comprobar
 * @param secondNumber Segundo numero a comprobar
 *
 * @return Booleano
 */
bool areIntegersEqual(int firstNumber, int secondNumber){
    return firstNumber == secondNumber;
}

/**
 * Verifica si el año de nacimientos de una persona es mayor a otra edad
 *
 * @param birthdayYear Año de nacimientos a comporar
 * @param olderAge Edad mayor a comprobar
 * @return Booleano
 */
bool isOlderThan(int birthdayYear, int olderAge){
    bool isValidAge = true;
    if (calcularEdad(birthdayYear) < olderAge) {
        printf("Error, Debes de tener mas de %d a\xf1os.\n", olderAge);
        isValidAge = false;
    }
    return isValidAge;
}
bool isLessThan(int birthdayYear, int olderAge){
    bool isValidAge = true;
    if (calcularEdad(birthdayYear) > olderAge) {
        printf("Error, Debes de tener menos de %d a\xf1os.\n", olderAge);
        isValidAge = false;
    }
    return isValidAge;
}

/**
 * Valida los 3 valores de una fecha Año, Mes y Dia
 *
 * @param day Dia de la fehca
 * @param month Mes de la fecha
 * @param year Año de la fecha
 * @return Booleano
 */
bool isValidDate(int day, int month, int year) {
    bool isValidDate = true;
    if (year < 0) {
        printf("Error, A\xf1o no puede ser 0.\n");
        isValidDate = false;
    }
    if (isValidDate && month < 1 || month > 12) {
        printf("Error, Mes no puede ser menor a 1 o mayor 12\n");
        isValidDate = false;
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) daysInMonth[1] = 29;

    if(isValidDate && !(day > 0 && day <= daysInMonth[month-1])){
        printf("Error, el mes %d no tiene el dia %d.\n", month, day);
        isValidDate = false;
    }
    return isValidDate;
}

/**
 * Verifica si el año es bisiesto
 *
 * @param year Año a verificar
 * @return Booleano
 */
bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

/**
 * Valida si un nuemero se encuentra dentro de un arreglo de numeros
 *
 * @param number Numero a verificar
 * @param numbers Arreglo de numeros
 * @return Booleano
 */
bool numberIsFoundIn(int number, const int numbers[]) {
    int i = 0;
    bool numberIsFound = false;
    while (!numberIsFound && numbers[i] != -99) {
        if (number == numbers[i]) numberIsFound = true;
        i++;
    }
    return numberIsFound;
}

// Función para validar si una fecha está entre otras dos fechas
bool dateIsBetween(const char *date, const char *startDate, const char *endDate) {
    int startComp = compararFechas(date, startDate);
    int endComp = compararFechas(date, endDate);

    return (startComp >= 0) && (endComp <= 0);
}

/**
 * Valida el formato del DNI
 *
 * @param dni Puntero del string del DNI para validar
 * @return booleano
 */
bool isValidDNI(const char* dni){
    return isStringOnlyHasNumber(dni, "DNI") && isStringLengthEqualTo(dni, "DNI", 8);
}

/**
 * Valida el formato del Telefono
 *
 * @param dni Puntero del string del telefono para validar
 * @return booleano
 */
bool isCellphoneValid(const char* cellphone){
    return isStringOnlyHasNumber(cellphone, "telefono") && isStringLengthEqualTo(cellphone, "telefono", 10);
}

/**
 * Valida el formato del nombre
 *
 * @param dni Puntero del string del nombre para validar
 * @return booleano
 */
bool isNameValid(const char* name, const char* nameType){
    return doesStringNotContainDigits(name, nameType) && isStringLengthGreaterThan(name, nameType, 2);
}

bool isAddressValid(const char* address){
    return doesStringNotContainDigits(address, "direccion") && isStringLengthGreaterThan(address, "direccion", 3);
}

bool validarOpciones(const int opcion, const int* opcionesValidas){
    bool opcionEsValida = false;
    opcionEsValida = numberIsFoundIn(opcion, opcionesValidas);
    if(!opcionEsValida) imprimirMensaje("Opcio no valida.", RED_COLOR);
    return opcionEsValida;
}

/**
 * Verifica si el sistema operativo es Windows
 * @return
 */
bool isWindowsOS(){
    const char* os = getenv("OS");
    return areStringsEqual(os, "Windows_NT");
}