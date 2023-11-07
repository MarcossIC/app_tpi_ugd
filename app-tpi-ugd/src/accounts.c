//
// Created by usuario on 28/10/2023.
//
#include "accounts.h"
#include "validateData.h"

/**
 * Solicita un String por valido por teclado
 *
 * @param inputName Nombre del input que se quiere solicitar
 * @param input Puntero del String donde se guardara el valor
 */
void getValidStringInput(const char* inputName, char* input){
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
                inputValid = isDniValid(input);
            } else if(inputValid && (areStringsEqual(inputName, "nombre") ||  areStringsEqual(inputName, "apellido"))){
                inputValid = isNamesValid(input, inputName);
            } else if(inputValid && areStringsEqual(inputName, "telefono")){
                inputValid = isCellphoneValid(input);
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
int readIntegerInput(const char* prompt) {
    int value = 0;
    bool inputValid = true;
    char buffer[20];
    do {
        printf("%s", prompt);
        scanf("%s", buffer);
        size_t length = strlen(buffer);
        if (length > 0 && buffer[length - 1] == '\n')buffer[length - 1] = '\0';
        else while (fgetc(stdin) != '\n') {}
        if (sscanf(buffer, "%d", &value) != 1) {
            printf("Error, Debes ingresar un numero valido.\n");
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
void getValidDate(const char* dateName, char* date){
    bool isDateValid = true;
    int day, month, year;
    do {
        printf("Ingresa su Fecha de %s \n", dateName);
        day = readIntegerInput("Dia:");
        month = readIntegerInput("Mes:");
        year = readIntegerInput("Año:");

        isDateValid = isValidDate(day, month, year);
        if(isDateValid && areStringsEqual(dateName, "nacimiento")) isDateValid = isOlderThan(year, 6);
        //Formato de la fecha
        snprintf(date, 11, "%04d-%02d-%02d", year, month, day);
        fflush(stdin);
    } while(isDateValid == false);
}

/**
 * Solicita un struct de Account con los datos por teclado
 *
 * @return Retorna el struct de account
 */
struct Account getAccountValidInput(){
    struct Account account = {"", "", "", "", "", "", 0};
    fflush(stdin);
    getValidStringInput("nombre", account.name);
    getValidStringInput("apellido", account.lastName);
    getValidStringInput("dni", account.dni);
    getValidStringInput("telefono", account.cellphone);
    getValidDate("nacimiento", account.birthDay);
    getValidStringInput("direccion", account.address);
    bool isTypeValid = false;
    do {
        printf("Dime cual es su tipo de cuenta\n");
        printf("1 - Normal\n");
        printf("2 - Beneficio Estudiante\n");
        printf("3 - Beneficio malvinas\n");
        account.type = readIntegerInput(":");
        isTypeValid = areIntegersEqual(account.type, 1) || areIntegersEqual(account.type, 2) || areIntegersEqual(account.type, 3);
        if(!isTypeValid){
            printf("El tipo que ingreso no es una opcion valida");
        }

    } while(!isTypeValid);

    return account;
}

/**
 * Guarda un account en el archivo "Users.dat"
 *
 * @param account struct account con los datos para guardar
 * @return Estado del resultado (1 hubo error / 0 no hubo error)
 */
int saveAccount(struct Account account) {
    FILE* userFile;
    int errors = 0;
    if((userFile = fopen("assets/Users.dat", "a+b")) != NULL){
        fwrite(&account, sizeof(struct Account), 1, userFile);
        fclose(userFile);
    } else {
        printf("Error, no se ha podido abrir el archivo.\n");
        errors = 1;
    }
    return errors;
}

/**
 * Lista todos las cuentas guardadas en el archivo Users.dat
 *
 * @return El numero de cuentas que listo
 */
int listAllRegisteredAccounts(){
    FILE* file;
    struct Account account;
    int registeredAccountCount = 0;
    if((file = fopen("assets/Users.dat", "r+b")) != NULL) {
        while (fread(&account, sizeof(struct Account), 1, file) == 1){
            printf("*******************************************************************************\n");
            printf("%s  \n",account.birthDay);
            printf("*******************************************************************************\n");
            registeredAccountCount++;
        }
        fclose(file);
    }
    return registeredAccountCount;
}

/**
 * Valida el formato del DNI
 *
 * @param dni Puntero del string del DNI para validar
 * @return booleano
 */
bool isDniValid(const char* dni){
    return isStringOnlyHasNumber(dni, "dni") && isStringLengthEqualTo(dni, "dni", 8);
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
bool isNamesValid(const char* name, const char* nameType){
    return doesStringNotContainDigits(name, nameType) && isStringLengthGreaterThan(name, nameType, 2);
}