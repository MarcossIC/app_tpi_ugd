#include "inputs.h"

/**
 * Solicita un String por valido por teclado
 *
 * @param nombreInput Nombre del input que se quiere solicitar.
 * @param input Puntero del String donde se guardara el valor.
 */
void escribirStringValido(const char* nombreInput, char* input){
    bool esValidoElInput = true;
    char buffer[100];
    do {
        printf("Ingresa su %s:", nombreInput);
        //Ingresa el valor en buffer
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            size_t length = strlen(buffer);
            //Limpia el buffer y la consola
            if (length > 0 && buffer[length - 1] == '\n')buffer[length - 1] = '\0';
            else while (fgetc(stdin) != '\n') {}

            strcpy(input, buffer);
            setColorOutput(RED_COLOR);
            //Validaciones
            esValidoElInput = isStringLengthLessThan(input, nombreInput, 50);
            if(esValidoElInput && areStringsEqual(nombreInput, "DNI")){
                esValidoElInput = isValidDNI(input);
            } else if(esValidoElInput && (areStringsEqual(nombreInput, "nombre") || areStringsEqual(nombreInput, "apellido"))){
                esValidoElInput = isNameValid(input, nombreInput);
            } else if(esValidoElInput && areStringsEqual(nombreInput, "telefono")){
                esValidoElInput = isCellphoneValid(input);
            }
            resetColor();
            fflush(stdin);
        }
    } while(!esValidoElInput);
}

/**
 *
 * @param prompt
 * @return
 */
float escribirNumeroDecimalValido(const char* prompt) {
    float value = 0;
    bool esValidoELInput;
    char buffer[20];
    do {
        esValidoELInput = true;
        printf("%s", prompt);
        scanf("%s", buffer);

        size_t length = strlen(buffer);
        //Elimina saltos de lineas del buffer
        if (length > 0 && buffer[length - 1] == '\n') buffer[length - 1] = '\0';
        else while (fgetc(stdin) != '\n') { }

        //sscanf = Transforma el string a int, si el string es un numero valido
        if (sscanf(buffer, "%f", &value) != 1) {
            setColorOutput(RED_COLOR);
            printf("Error, Debes ingresar un numero valido.\n");
            resetColor();
            esValidoELInput = false;
        }

        fflush(stdin);
    } while (!esValidoELInput);

    return value;
}

float escribirMontoValido(const char* prompt, float limite, float minimo){
    bool esValidoElMonto;
    float monto = 0;
    do {
        esValidoElMonto = true;
        monto = escribirNumeroDecimalValido(prompt);
        char mensaje[60];
        if(monto > limite){
            esValidoElMonto = false;
            snprintf(mensaje, 60, "El monto %.2f no puede pasar su limite de %.2f", monto, limite);
            imprimirMensaje(mensaje, RED_COLOR);
        }
        if(monto < minimo){
            esValidoElMonto = false;
            snprintf(mensaje, 60, "El valor del pasaje es %.2f", minimo);
            imprimirMensaje(mensaje, RED_COLOR);
        }
    } while (!esValidoElMonto);
    return monto;
}

/**
 * Solicita un Entero por teclado
 *
 * @param prompt Mensaje que se mouestra en consola al solicitar
 * @return Retorna el entero que se escribio
 */
int escribirEnteroValido(const char* prompt) {
    int value = 0;
    bool inputValid;
    char buffer[20];
    do {
        inputValid = true;
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
    bool isDateValid;
    int day, month, year;
    do {
        isDateValid = true;
        printf("Ingresa su Fecha de %s \n", dateName);
        day = escribirEnteroValido("Dia:");
        month = escribirEnteroValido("Mes:");
        year = escribirEnteroValido("Año:");

        isDateValid = isValidDate(day, month, year);
        if(isDateValid && areStringsEqual(dateName, "nacimiento")) isDateValid = isOlderThan(year, 6);
        //Formato de la fecha
        snprintf(date, 11, "%04d-%02d-%02d", year, month, day);
        fflush(stdin);
    } while(!isDateValid);
}

/**
 *
 * @return
 */
int recuperarHoraActual(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int horaActual = tm.tm_hour;
    return horaActual;
}

void recuperarFechaActual(char* date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, 11, "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
}