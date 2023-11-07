
#include "utilidades.h"

/**
 * Comprueba si dos Strings son iguales
 *
 * @param firstString Primer string a comprar
 * @param secondString Segundo string a comparar
 *
 * @return Booleano
 */
bool areStringsEqual(const char* firstString, const char* secondString){
    bool areStringsEqual = false;
    if (strcmp(firstString, secondString) == 0) areStringsEqual = true;
    return areStringsEqual;
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
        setColorOutput(RED_COLOR);
        printf("Error, El %s no puede ser mayor a %d caracteres.\n", stringName, minSize);
        resetColor();
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
        setColorOutput(RED_COLOR);
        printf("Error, El %s no puede ser menor a %d caracteres.\n", stringName, maxSize);
        resetColor();
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
 *
 * @return Booleano
 */
bool isStringLengthBetween(const char* string, const char* stringName, int minSize, int maxSize){
    bool isStringLengthBetween = true;
    int lenght = strlen(string);
    if(lenght > minSize && lenght < maxSize){
        setColorOutput(RED_COLOR);
        printf("Error, El tamanio de %s no es valido, debe de estar entre %d y %d\n", stringName, minSize, maxSize);
        resetColor();
        isStringLengthBetween = false;
    }
    return isStringLengthBetween;
}


/**
 * Comprueba si el String no contiene numeros
 *
 * @param string Puntero al string a verificar
 * @param stringName Nombre del String
 *
 * @return Booleano
 */
bool doesStringNotContainDigits(const char* string, const char* stringName){

    bool doesStringNotContainDigits = true;
    //En caso de tener false
    if (strcspn(string, "0123456789") < strlen(string)) {
        doesStringNotContainDigits =  false;//False, es que si contiene
        setColorOutput(RED_COLOR);
        printf("Error, El %s no puede contener numeros.\n", stringName);
        resetColor();
    }
    return doesStringNotContainDigits;
}

/**
 * Comprueba que el String solo contenga numeros
 *
 * @param string Puntero al String a verificar
 * @param stringName Nombre del String
 *
 * @return Booleano
 */
bool isStringOnlyHasNumber(const char *string, const char* stringName){
    bool isStringOnlyHasNumber = true;
    int value = 0;
    if (sscanf(string, "%d", &value) != 1) {
        setColorOutput(RED_COLOR);
        printf("Error, El %s solo puede tener numeros.\n", stringName);
        resetColor();
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
 *
 * @return Booleano
 */
bool isStringLengthEqualTo(const char *string, const char* stringName, int size){
    bool isStringLengthEqualTo = true;
    if ( !areIntegersEqual(strlen(string), size)) {
        isStringLengthEqualTo = false;
        setColorOutput(RED_COLOR);
        printf("Error, el tamanioo del %s no puede ser distinto de %d\n",stringName, size);
        resetColor();
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
 *
 * @return Booleano
 */
bool isOlderThan(int birthdayYear, int olderAge){
    bool isValidAge = true;
    if (calcUserAge(birthdayYear) < olderAge) {
        setColorOutput(RED_COLOR);
        printf("Error, Debes de tener mas de %d años.\n", &olderAge);
        resetColor();
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
 *
 * @return Booleano
 */
bool isValidDate(int day, int month, int year) {
    bool isValidDate = true;
    setColorOutput(RED_COLOR);
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
    resetColor();
    return isValidDate;
}

/**
 * Calcula la edad actual de la persona segun un año
 *
 * @param year Año de nacimiento
 *
 * @return Edad que tendria este año
 */
int calcUserAge(int year){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;

    return currentYear - year;
}

/**
 * Verifica si el año es bisiesto
 *
 * @param year Año a verificar
 *
 * @return Booleano
 */
bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

bool encontrarCoincidencia(int number, const int numbers[]) {
    int i = 0;
    bool esNumeroIgualA = false;
    while (!esNumeroIgualA && numbers[i] != -99) {
        if (number == numbers[i]) esNumeroIgualA = true;
        i++;
    }
    return esNumeroIgualA;
}

/**
 * Ejecuta un comando para limpiar la consola segun el sistema ope<rativo
 */
void clearConsole() {

    if (isWindowsOS()) {
        system("cls");
    } else {
        system("clear");
    }
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

bool isWindowsOS(){
    const char* os = getenv("OS");
}