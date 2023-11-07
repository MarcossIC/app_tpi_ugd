//
// Created by usuario on 6/11/2023.
//

#include "inputs.h"
#include "utilidades.h"

/**
 * Solicita un String por valido por teclado
 *
 * @param inputName Nombre del input que se quiere solicitar.
 * @param input Puntero del String donde se guardara el valor
 */
void escribirStringValido(const char* inputName, char* input){
    bool inputValid = true;
    char buffer[100];
    do {
        printf("Ingresa su %s:", inputName);
        //Ingresa el valor en buffer
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t length = strlen(buffer);
            //Limpia el buffer y la consola
            if (length > 0 && buffer[length - 1] == '\n')buffer[length - 1] = '\0';
            else while (fgetc(stdin) != '\n') {}

            strcpy(input, buffer);

            //Valida
            inputValid = isStringLengthLessThan(input, inputName, 50);
            if(inputValid && areStringsEqual(inputName, "dni")){
                inputValid = esValidoElDNI(input);
            } else if(inputValid && (areStringsEqual(inputName, "nombre") ||  areStringsEqual(inputName, "apellido"))){
                inputValid = esValidoElNombre(input, inputName);
            } else if(inputValid && areStringsEqual(inputName, "telefono")){
                inputValid = esValidoElTelefono(input);
            }

            fflush(stdin);
        }
    } while(!inputValid);
}

/**
 * Solicita un Entero por teclado
 *
 * @param prompt Mensaje que se mouestra en consola al solicitar
 * @return Retorna el entero que se escribio
 */
int escribirEnteroValido(const char* prompt) {
    int value = 0;
    bool inputValid = true;
    char buffer[20];
    do {
        printf("%s", prompt);
        scanf("%s", buffer);

        size_t length = strlen(buffer);
        //Elimina saltos de lineas del buffer
        if (length > 0 && buffer[length - 1] == '\n') buffer[length - 1] = '\0';
        else while (fgetc(stdin) != '\n') { }

        //sscanf = Transforma el string a int, si el string es un numero valido
        if (sscanf(buffer, "%d", &value) != 1) {
            setColorOutput(RED_COLOR);
            printf("Error, Debes ingresar un numero valido.\n");
            resetColor();
            inputValid = false;
        }

        fflush(stdin);
    } while (!inputValid);

    return value;
}

/**
 * Solicita una fecha por teclado valida
 * La fecha es devuelta en formato "yyyy-mm-dd"
 *
 * @param dateName Nombre del tipo de fecha que se solicita
 * @param date Puntero a la variable donde se guardara la fecha
 */
void escribirFechaValida(const char* dateName, char* date){
    bool isDateValid = true;
    int day, month, year;
    do {
        printf("Ingresa su Fecha de %s \n", dateName);
        day = escribirEnteroValido("Dia:");
        month = escribirEnteroValido("Mes:");
        year = escribirEnteroValido("Año:");

        isDateValid = isValidDate(day, month, year);
        if(isDateValid && areStringsEqual(dateName, "nacimiento")) isDateValid = isOlderThan(year, 6);
        //Formato de la fecha
        snprintf(date, 11, "%04d-%02d-%02d", year, month, day);
        fflush(stdin);
    } while(isDateValid == false);
}

/**
 * Valida el formato del DNI
 *
 * @param dni Puntero del string del DNI para validar
 * @return booleano
 */
bool esValidoElDNI(const char* dni){
    return isStringOnlyHasNumber(dni, "dni") && isStringLengthEqualTo(dni, "dni", 8);
}

/**
 * Valida el formato del Telefono
 *
 * @param dni Puntero del string del telefono para validar
 * @return booleano
 */
bool esValidoElTelefono(const char* cellphone){
    return isStringOnlyHasNumber(cellphone, "telefono") && isStringLengthEqualTo(cellphone, "telefono", 10);
}

/**
 * Valida el formato del nombre
 *
 * @param dni Puntero del string del nombre para validar
 * @return booleano
 */
bool esValidoElNombre(const char* name, const char* nameType){
    return doesStringNotContainDigits(name, nameType) && isStringLengthGreaterThan(name, nameType, 2);
}