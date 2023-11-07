//
// Created by usuario on 28/10/2023.
//
#include "user.h"
#include "utilidades.h"
#include "inputs.h"

/**
 * Arma el struct de Usuario con todos los datos
 *
 * @return Retorna el struct de account
 */
struct Usuario crearNuevoUsuarioValido(){
    struct Usuario account = {"", "", "", "", "", "", 0};
    fflush(stdin);
    escribirStringValido("nombre", account.nombre);
    escribirStringValido("apellido", account.apellido);
    escribirStringValido("dni", account.dni);
    escribirStringValido("telefono", account.telefono);
    escribirFechaValida("nacimiento", account.fechaNacimiento);
    escribirStringValido("direccion", account.direccion);
    bool isTypeValid = false;
    do {
        printf("Dime cual es su tipo de cuenta\n");
        printf("1 - Normal(Sin beneficio.)\n");
        printf("2 - Boleto Estudiantil.\n");
        printf("3 - Beneficio Discapacidad.\n");
        printf("4 - Beneficio Anciano.\n");
        printf("5 - Beneficio por ex combatiente de malvinas.\n");

        account.tipo = escribirEnteroValido(":");
        isTypeValid = areIntegersEqual(account.tipo, 1) || areIntegersEqual(account.tipo, 2) || areIntegersEqual(account.tipo, 3) || areIntegersEqual(account.tipo, 4) || areIntegersEqual(account.tipo, 5);

        if(!isTypeValid) {
            setColorOutput(RED_COLOR);
            printf("El tipo que ingreso no es una opcion valida.\n");
            resetColor();
        }
    } while(!isTypeValid);

    return account;
}

/**
 * Guarda un account en el archivo "Users.dat"
 *
 * @param user struct account con los datos para guardar
 * @return Estado del resultado (1 hubo error / 0 no hubo error)
 */
int guardarUsuario(struct Usuario user) {
    FILE* userFile;
    int errors = 0;
    if((userFile = fopen("assets/Users.dat", "a+b")) != NULL){
        fwrite(&user, sizeof(struct Usuario), 1, userFile);
        fclose(userFile);
    } else errors = 1;
    return errors;
}

/**
 * Lista todos las cuentas guardadas en el archivo Users.dat
 *
 * @return El numero de cuentas que listo
 */
int listarTodosLosUsuariosRegistrados(){
    FILE* file;
    struct Usuario account;
    int registeredAccountCount = 0;
    if((file = fopen("assets/Users.dat", "r+b")) != NULL) {
        while (fread(&account, sizeof(struct Usuario), 1, file) == 1){
            printf("*******************************************************************************\n");
            printf("%s  \n",account.fechaNacimiento);
            printf("*******************************************************************************\n");
            registeredAccountCount++;
        }
        fclose(file);
    }
    return registeredAccountCount;
}