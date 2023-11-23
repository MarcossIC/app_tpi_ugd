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
            } else if(esValidoElInput && areStringsEqual(nombreInput, "direccion")){
                esValidoElInput = isAddressValid(input);
            }
            resetColor();
            fflush(stdin);
        }
    } while(!esValidoElInput);
}

/**
 * Pide por teclado un numero decimal valido
 *
 * @param prompt Mensaje para mostrar al usuario al solicitaar
 * @return
 */
float escribirNumeroDecimalValido(const char* prompt) {
    float value = 0;
    bool esValidoELInput;
    char buffer[20];
    do{
        esValidoELInput = true;
        printf("%s", prompt);
        if(scanf("%f", &value) != 1){
            imprimirMensaje("Error, Debes ingresar un numero valido.", RED_COLOR);
            esValidoELInput = false;
        }
        fflush(stdin);
    } while (!esValidoELInput);
    return value;
}

/**
 * Solicita un monto valido por teclado
 *
 * @param prompt Mensaje para solicitar el monto
 * @param limite Limite maximo del monto
 * @param minimo Valor minimo del monto
 * @return
 */
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
            snprintf(mensaje, 60, "El minimo es %.2f", minimo);
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
int escribirEnteroValido(const char* prompt, bool esBinario) {
    int value = 0;
    bool inputValid;
    do{
        inputValid = true;
        printf("%s", prompt);
        if(scanf("%d", &value) != 1){
            imprimirMensaje("No es un valor valido", RED_COLOR);
            inputValid = false;
        }
        fflush(stdin);
        if(esBinario){
            int opcionesValidas[] = {1, 0, -99};
            inputValid = numberIsFoundIn(value, opcionesValidas);
            if(!inputValid) imprimirMensaje("No es una opcion valida", YELLOW_COLOR);
        }
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
    bool esUnaFechaValida;
    int day, month, year;
    do {
        esUnaFechaValida = true;
        printf("Ingresa su Fecha de %s \n", dateName);
        day = escribirEnteroValido("Dia:", false);
        month = escribirEnteroValido("Mes:", false);
        year = escribirEnteroValido("A\xf1o:", false);

        esUnaFechaValida = isValidDate(day, month, year);


        if(esUnaFechaValida && areStringsEqual(dateName, "nacimiento")) {
            esUnaFechaValida = isOlderThan(year, 6) && isLessThan(year, 100);
        }

        //Formato de la fecha
        snprintf(date, 11, "%04d-%02d-%02d", year, month, day);
        fflush(stdin);
    } while(!esUnaFechaValida);
}

/**
 * Solicita una direccion valida por teclado
 * Direccion entre Posadas - Garupa - Candelaria
 *
 * @param nombreDireccion Nombre o tipo de direccion, ejemplo "direccion", "origen", "destino"
 * @return
 */
int escribirDireccionValida(const char* nombreDireccion){
    bool direccionValida = false;
    int direccion = 0;
    do{
        printf("Dime cual es tu %s:",nombreDireccion);
        direccion = escribirEnteroValido("\n1 - Posadas\n2 - Garupa\n3 - Candelaria\n:", false);
        int opcionesValidas[] = {1,2,3,-99};
        direccionValida = validarOpciones(direccion, opcionesValidas);
    } while(!direccionValida);

    return direccion;
}

/**
 * Recupera la hora actual del sistema
 * @return
 */
int recuperarHoraActual(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int horaActual = tm.tm_hour;
    return horaActual;
}

/**
 * Recupera el año acutal del sistema
 * Nombre en ingles por la "ñ"
 * @return
 */
int getCurrentYear(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year;
    return currentYear;
}

/**
 * Recupera fecha actual del sistema
 * @param date
 */
void recuperarFechaActual(char* date){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(date, 11, "%04d-%02d-%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday);
}

